#ifndef CCLIBXML_H
#define CCLIBXML_H

/*------------------------------------------------------------------------------------------------------*/
/**
 * \file:       CCLibXml.h
 * \brief       XML Basic Library
 *
 * \author:     Vincenzo Calabrò <vincenzo@calabrothers.com>
 *
 * \defgroup    XML XML Basic Library
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
/** \addtogroup XML
 *  @{
 */

#include <CCTypes.h>
#include <QtXml>


namespace CC {
namespace XML {

class Node {
protected:
    QDomElement     m_Node;
public:
    Node();
    Node(QDomElement node);

public:
    qbool       hasChild(QString sNode) const;
    Node        getChild(QString sNode);

    Node        nextSibling();

    Node        operator()(QString sNode);

    qbool       hasAttribute(QString sAttribute) const;
    QString     getAttribute(QString sAttribute);

    QString     getValue();
    qbool       isValid() const;

    void        printNode(int nDepth = 0) const;

};

class Parser {

protected:
    QDomDocument    m_XmlDoc;
    QString         m_Filename;
    qbool           m_bValid;
    QDomElement     m_Node;

public:
    Parser(QString sFname);

public:
    qbool       isValid() const;
    Node        getRoot();
};

}
}

/** @}*/

#endif // CCLIBXML_H
