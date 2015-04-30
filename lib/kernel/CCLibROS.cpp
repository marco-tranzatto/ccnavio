#include <CCLibROS.h>
#include <QDebug>
#include <QMutexLocker>

using namespace CC;

/*------------------------------------------------------------------------------------------------------*/
CC::ROS::QROSModule::QROSModule(QString sNodeID, qint32  argc, qchar** argv):
    m_sNodeID(sNodeID),
    m_bIsInitialized(false),
    m_bIsRunning(false),
    m_bIsStopped(false),
    m_bIsPeriodic(false),
    m_pRate(NULL),
    m_pNode(NULL),
    m_Parser("ccsettings.xml")
{
    m_bHasConf       = false;
    m_bIsPeriodic    = false;
    m_rFrequency     = 0.0;

    qDebug() << "ROS::QROSModule::QROSModule XML Config Enable (" << m_Parser.isValid() << ")";
    if (m_Parser.isValid()) {
        CC::XML::Node root = m_Parser.getRoot();

        qDebug() << "ROS::QROSModule::QROSModule XML File Content:";
        root.printNode();

        CC::XML::Node module = root.getChild("module");

        while(module.isValid()) {
            if (module.getAttribute("id") == sNodeID) {
                qDebug() << "ROS::QROSModule::QROSModule Module " << sNodeID << " has XML Configuration!";
                m_Conf      = module;
                m_bHasConf  = true;
                break;
            }
            module = module.nextSibling();
        }
    }

    qDebug() << "ROS::QROSModule::QROSModule Creating new module named " << sNodeID;
    if (argv == NULL)
    {
        ros::M_string remappings;

        if (hasConf()) {
            CC::XML::Node masterNode  = getConf().getChild("master");
            if (!masterNode.getValue().isEmpty()){
                qDebug() << "ROS::QROSModule::QROSModule Overriding master URL to " << masterNode.getValue();
                remappings["__master"] = masterNode.getValue().toStdString();
            }
            CC::XML::Node ipNode  = getConf().getChild("ip");
            if (!ipNode.getValue().isEmpty()){
                qDebug() << "ROS::QROSModule::QROSModule Overriding IP to " << ipNode.getValue();
                remappings["__ip"] = ipNode.getValue().toStdString();
            }
            CC::XML::Node hostnameNode  = getConf().getChild("hostname");
            if (!hostnameNode.getValue().isEmpty()){
                qDebug() << "ROS::QROSModule::QROSModule Overriding hostname to " << hostnameNode.getValue();
                remappings["__hostname"] = hostnameNode.getValue().toStdString();
            }
            CC::XML::Node namespaceNode  = getConf().getChild("namespace");
            if (!namespaceNode.getValue().isEmpty()){
                qDebug() << "ROS::QROSModule::QROSModule Overriding namespace to " << namespaceNode.getValue();
                remappings["__ns"] = namespaceNode.getValue().toStdString();
            }

        }
        ros::init(remappings, m_sNodeID.toStdString());

    } else  {
        int     sysArgc = argc;
        char**  sysArgv = argv;
        ros::init(sysArgc, sysArgv, m_sNodeID.toStdString());
    }

    m_pNode = new ros::NodeHandle();

    m_bIsInitialized = true;

    if (hasConf()) {
        qDebug() << "ROS::QROSModule::QROSModule Start Autoconfigure...";
        CC::XML::Node periodic  = getConf().getChild("periodic");

        if (periodic.getValue() == "true") {
            qDebug() << "ROS::QROSModule::QROSModule Module is periodic";
            m_bIsPeriodic = true;

            CC::XML::Node frequency = getConf().getChild("frequency");
            qbool         bValid    = false;

            if (!frequency.getValue().isEmpty()){
                m_rFrequency = frequency.getValue().toDouble(&bValid);

                if (bValid) {
                    qDebug() << "ROS::QROSModule::QROSModule Frequency to " << m_rFrequency << "Hz";
                    setFrequency(m_rFrequency);
                }
            }
        }
        qDebug() << "ROS::QROSModule::QROSModule End Autoconfigure...";
    }

    onConnect();
}

/*------------------------------------------------------------------------------------------------------*/
qbool CC::ROS::QROSModule::hasConf() const
{
    return m_bHasConf;
}

/*------------------------------------------------------------------------------------------------------*/
CC::XML::Node& CC::ROS::QROSModule::getConf()
{
    return m_Conf;
}

/*------------------------------------------------------------------------------------------------------*/
ROS::Time ROS::QROSModule::getTime() const
{
    return ros::Time::now();
}

/*------------------------------------------------------------------------------------------------------*/
void ROS::QROSModule::onConnect()
{
    qDebug() << "ROS::QROSModule::onConnect() Connected";
}

/*------------------------------------------------------------------------------------------------------*/
void ROS::QROSModule::onDisconnect()
{
    qDebug() << "ROS::QROSModule::onDisconnect() Disconnected";
}

/*------------------------------------------------------------------------------------------------------*/
CC::ROS::Node& CC::ROS::QROSModule::getNode()
{
    return *m_pNode;
}

/*------------------------------------------------------------------------------------------------------*/
CC::ROS::QROSModule::~QROSModule()
{

    if (m_pNode != NULL)
    {
        onDisconnect();
        delete m_pNode;        

    }

    if (m_pRate != NULL)
    {
        delete m_pRate;
    }

    qDebug() << "ROS::QROSModule::~QROSModule quit()";
    quit();

    qDebug() << "ROS::QROSModule::~QROSModule wait()";
    wait();

    qDebug() << "ROS::QROSModule::~QROSModule end of distructor";    
}

/*------------------------------------------------------------------------------------------------------*/
void CC::ROS::QROSModule::setFrequency(qreal rFrequency)
{
    qDebug() << "ROS::QROSModule::setFrequency() Setting frequency to " << rFrequency << "Hz";

    if (m_pRate != NULL)
    {
        delete m_pRate;
    }

    if (rFrequency > 0.0) {
        qDebug() << "ROS::QROSModule::setFrequency() OK";
        m_rFrequency    = rFrequency;
        m_pRate         = new ros::Rate(m_rFrequency);
        m_bIsPeriodic   = true;
    } else {
        qDebug() << "ROS::QROSModule::setFrequency() ERROR, set aperiodic and removing timer";
        m_rFrequency    = 0.0;
        m_bIsPeriodic   = false;
    }
}

/*------------------------------------------------------------------------------------------------------*/
void CC::ROS::QROSModule::stop()
{
    qDebug() << "ROS::QROSModule::stop() Stopping ROS module";
    QMutexLocker locker(&m_Mutex);
    m_bIsRunning = false;
    if (m_bIsStopped == false) {
        onStop();
        m_bIsStopped = true;
    }
    ros::shutdown();
}

/*------------------------------------------------------------------------------------------------------*/
void CC::ROS::QROSModule::onStart()
{
   qDebug() << "ROS::QROSModule::onStart() Starting code execution";
}

/*------------------------------------------------------------------------------------------------------*/
void CC::ROS::QROSModule::onStop()
{
   qDebug() << "ROS::QROSModule::onStop() Stopping code execution";
}

/*------------------------------------------------------------------------------------------------------*/
void CC::ROS::QROSModule::run()
{
    qDebug() << "ROS::QROSModule::run() Running main thread";
    m_bIsRunning = true;

    onStart();

    if (m_bIsPeriodic == false)
    {

        runningCode();

        ros::spin();

    } else {


        while (ros::ok())
        {
            {
                QMutexLocker locker(&m_Mutex);
                if (m_bIsRunning == false) break;
            }

            runningCode();

            ros::spinOnce();

            if (m_bIsPeriodic == true)
            {
                if (m_pRate != NULL)
                {
                    m_pRate->sleep();
                }
            } else {
                break;
            }
        }

    }

    if (m_bIsStopped == false) {
        onStop();
        m_bIsStopped = true;
    }

    stop();
    exec();
}

