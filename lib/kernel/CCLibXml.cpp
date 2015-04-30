#include <CCLibXml.h>
#include <QDebug>
#include <QFile>

using namespace CC;

/*------------------------------------------------------------------------------------------------------*/
XML::Parser::Parser(QString sFname):
    m_Filename(sFname), m_bValid(false)
{

    QFile file(m_Filename);

    // Try to open the file
    qDebug() << "XML::Parser::Parser Opening file " << m_Filename << "...";
    if (!file.open(QIODevice::ReadOnly))
    {
        // Error while loading file
        qDebug() << "PXML::Parser::Parser Error while loading file" << m_Filename;
        m_bValid = false;
        return;
    }

    // Set data into the QDomDocument before processing
    qDebug() << "XML::Parser::Parser Parsing XML content...";
    m_XmlDoc.setContent(&file);
    file.close();

    // Get the document root
    qDebug() << "XML::Parser::Parser Getting XML root";
    m_Node   = m_XmlDoc.documentElement();

    // Set flags
    qDebug() << "XML::Parser::Parser Setting Valid XML";
    m_bValid = true;
}

/*------------------------------------------------------------------------------------------------------*/
qbool XML::Parser::isValid() const
{
    return m_bValid;
}

/*------------------------------------------------------------------------------------------------------*/
XML::Node XML::Parser::getRoot()
{
    return Node(m_Node);
}

/*------------------------------------------------------------------------------------------------------*/
XML::Node::Node(QDomElement node): m_Node(node)
{
}

/*------------------------------------------------------------------------------------------------------*/
XML::Node::Node(): m_Node()
{
}

/*------------------------------------------------------------------------------------------------------*/
XML::Node XML::Node::nextSibling()
{
    QDomElement Sibling = m_Node.nextSibling().toElement();

    while(!Sibling.isNull())
    {
       if (Sibling.tagName() == m_Node.tagName()) {
            return Node(Sibling);
        }

        Sibling = Sibling.nextSibling().toElement();
    }

    return Sibling;
}

/*------------------------------------------------------------------------------------------------------*/
qbool XML::Node::hasChild(QString sNode) const
{
    QDomElement Child = m_Node.firstChild().toElement();

    while(!Child.isNull())
    {
        if (Child.tagName() == sNode) {
            //qDebug() << "Node " << sNode << " found!";
            return true;
        }

        Child = Child.nextSibling().toElement();
    }

    //qDebug() << "Node " << sNode << " NOT found!";

    return false;
}

/*------------------------------------------------------------------------------------------------------*/
XML::Node XML::Node::getChild(QString sNode)
{
    //qDebug() << "XML::Node::getChild() Searching (" << sNode << ") into " << m_Node.tagName();

    QDomElement Child = m_Node.firstChild().toElement();

    while(!Child.isNull())
    {
        //qDebug() << "XML::Node::getChild() Checking Child (" <<  Child.tagName() << ")";
        if (Child.tagName() ==  sNode) {
            //qDebug() << "XML::Node::getChild() Child (" <<  Child.tagName() << ") FOUND";
            return Node(Child);
        }

        Child = Child.nextSibling().toElement();
    }

    //qDebug() << "XML::Node::getChild() Nope...";
    return Child;
}

/*------------------------------------------------------------------------------------------------------*/
qbool XML::Node::isValid() const
{
    return !m_Node.isNull();
}

/*------------------------------------------------------------------------------------------------------*/
XML::Node XML::Node::operator()(QString sNode)
{
    return getChild(sNode);
}

/*------------------------------------------------------------------------------------------------------*/
qbool XML::Node::hasAttribute(QString sAttribute) const
{
    QDomElement Node = m_Node;

    while(!Node.isNull())
    {
        if (!Node.attribute(sAttribute).isEmpty()) {
            //qDebug() << "Attribute " << sAttribute << " found!";
            return true;
        }

        Node = Node.nextSibling().toElement();
    }

    //qDebug() << "Attribute " << sAttribute << " NOT found!";

    return false;
}

/*------------------------------------------------------------------------------------------------------*/
QString XML::Node::getAttribute(QString sAttribute)
{
    if (!hasAttribute(sAttribute)) {
        return QString();
    }

    QDomElement Node = m_Node;

    while(!Node.isNull())
    {
        if (!Node.attribute(sAttribute).isEmpty()) {
            return Node.attribute(sAttribute);
        }

        Node = Node.nextSibling().toElement();
    }

    return QString();
}

/*------------------------------------------------------------------------------------------------------*/
QString XML::Node::getValue()
{
    //qDebug() << "Getting value";
    return m_Node.firstChild().toText().data();
}

/*------------------------------------------------------------------------------------------------------*/
void XML::Node::printNode(int nDepth) const
{
    qint32  nDepth0(nDepth);

    QString space("|");
    QString line;
    for(;nDepth>0;nDepth--) {
        space = space + "-";
    }

    qDebug() << line.sprintf("%s%s", space.toStdString().c_str(), m_Node.tagName().toStdString().c_str());

    QDomElement Child = m_Node.firstChild().toElement();

    while(!Child.isNull())
    {

        Node(Child).printNode(nDepth0 + 1);

        Child = Child.nextSibling().toElement();
    }

}
