#ifndef CCLIBROS_H
#define CCLIBROS_H

/*------------------------------------------------------------------------------------------------------*/
/**
 * \file:       CCLibROS.h
 * \brief       ROS Wrapping Library
 *
 * \author:     Vincenzo Calabrò <vincenzo@calabrothers.com>
 *
 * \defgroup    ROS ROS Lrapping Library
 * \ingroup     CCLibrary
 */

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <CCTypes.h>
#include <CCPBC.h>
#include <CCLibXml.h>

#include <QThread>
#include <QString>
#include <QMap>
#include <QMutex>

/*------------------------------------------------------------------------------------------------------*/
/** \addtogroup ROS
 *  @{
 */

namespace CC {
namespace ROS {

typedef ros::Subscriber                     Subscriber;
typedef ros::Publisher                      Publisher;
typedef ros::NodeHandle                     Node;
typedef ros::Time                           Time;
typedef ros::Duration                       TimeDuration;
typedef ros::SubscriptionCallbackHelperPtr  CallBackFcn;
typedef ros::TransportHints                 TransportOpt;

class QROSModule : public QThread {    

    private:
        static  const   quint32                 m_unDefaultQueueSize = 1;
                QMutex                          m_Mutex;
    private:
                QString                         m_sNodeID;
                qbool                           m_bIsInitialized;
                qbool                           m_bIsRunning;
                qbool                           m_bIsStopped;
                qbool                           m_bIsPeriodic;
                qreal                           m_rFrequency;
                qbool                           m_bHasConf;
    private:
                ros::Rate*                      m_pRate;
                ROS::Node*                      m_pNode;
                XML::Parser                     m_Parser;
                XML::Node                       m_Conf;


    public slots:
        void stop();

    private:
        void run();

    public:
        QROSModule( QString  sNodeID,
                    qint32  argc = 0,
                    qchar** argv = NULL);

    public:

        void        setFrequency(  qreal rFrequency);

        ROS::Node&  getNode();

        qbool       hasConf() const;
        XML::Node&  getConf();

        ROS::Time   getTime() const;

        template <class T>
        Publisher  advertise(QString sTopic, qbool bLatch = true) {
            PBC_INIT
            PBC_PRECOND(m_bIsInitialized == true)   {   return Publisher(); }
            PBC_PRECOND(m_pNode != NULL)            {   return Publisher(); }
            return m_pNode->advertise<T>(sTopic.toStdString(), ROS::QROSModule::m_unDefaultQueueSize, bLatch);
        }

        template <class T>
        Publisher  advertise(QString sTopic, quint32 unQueueSize, qbool bLatch = true) {
            PBC_INIT
            PBC_PRECOND(m_bIsInitialized == true)   {   return Publisher(); }
            PBC_PRECOND(m_pNode != NULL)            {   return Publisher(); }
            return m_pNode->advertise<T>(sTopic.toStdString(), unQueueSize, bLatch);
        }

        template <class M, class T>
        Subscriber  subscribe(QString sTopic, T *pObj, void(T::*pFcn)(M), const TransportOpt& Options=TransportOpt()) {
            PBC_INIT
            PBC_PRECOND(m_bIsInitialized == true)   {   return Subscriber(); }
            PBC_PRECOND(m_pNode != NULL)            {   return Subscriber(); }
            return m_pNode->subscribe(sTopic.toStdString(), ROS::QROSModule::m_unDefaultQueueSize, pFcn, pObj, Options);
        }

        template <class M, class T>
        Subscriber  subscribe(QString sTopic, T *pObj, void(T::*pFcn)(M), quint32 unQueueSize, const TransportOpt& Options=TransportOpt()) {
            PBC_INIT
            PBC_PRECOND(m_bIsInitialized == true)   {   return Subscriber(); }
            PBC_PRECOND(m_pNode != NULL)            {   return Subscriber(); }
            return m_pNode->subscribe(sTopic.toStdString(), unQueueSize, pFcn, pObj, Options);
        }

        template <class M>
        Subscriber  subscribe(QString sTopic, void(*pFcn)(M), const TransportOpt& Options=TransportOpt()) {
            PBC_INIT
            PBC_PRECOND(m_bIsInitialized == true)   {   return Subscriber(); }
            PBC_PRECOND(m_pNode != NULL)            {   return Subscriber(); }
            return m_pNode->subscribe(sTopic.toStdString(), ROS::QROSModule::m_unDefaultQueueSize, pFcn, Options);
        }

        template <class M>
        Subscriber  subscribe(QString sTopic, void(*pFcn)(M), quint32 unQueueSize, const TransportOpt& Options=TransportOpt()) {
            PBC_INIT
            PBC_PRECOND(m_bIsInitialized == true)   {   return Subscriber(); }
            PBC_PRECOND(m_pNode != NULL)            {   return Subscriber(); }
            return m_pNode->subscribe(sTopic.toStdString(), unQueueSize, pFcn, Options);
        }

    protected:
        void onConnect();
        void onStart();
        void onStop();
        void onDisconnect();

    public:
        virtual void runningCode() = 0;
        virtual ~QROSModule();
};

}
}

/** @}*/



#endif // CCLIBROS_H
