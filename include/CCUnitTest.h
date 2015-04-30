#ifndef CCUNITTEST_H
#define CCUNITTEST_H

/*------------------------------------------------------------------------------------------------------*/
/**
 * \file:       CCUnitTest.h
 * \brief       Unit Test Support Functions
 *
 * \author:     Vincenzo Calabrò <vincenzo@calabrothers.com>
 *
 * \defgroup    UT Unit Test Support Functions
 * \ingroup     CCLibrary
 */

#include <QtTest/QTest>
#include <QList>
#include <QString>
#include <QSharedPointer>
#include <QDebug>

/*------------------------------------------------------------------------------------------------------*/
/** \addtogroup UT
 *  @{
 */

namespace CC
{
namespace UNITTEST
{

/*------------------------------------------------------------------------------------------------------*/
typedef QList<QObject*> CCUnitTestList;

/*------------------------------------------------------------------------------------------------------*/
inline CCUnitTestList& getUnitTestList()
{
    static CCUnitTestList gCCUnitTestList;
    return gCCUnitTestList;
}

/*------------------------------------------------------------------------------------------------------*/
inline bool findUnitTest(QObject* pObject)
{
    CCUnitTestList& list = getUnitTestList();
    if (list.contains(pObject))
    {
        return true;
    }
    foreach (QObject* pTest, list)
    {
        if (pTest->objectName() == pObject->objectName())
        {
            return true;
        }
    }
    return false;
}

/*------------------------------------------------------------------------------------------------------*/
inline void addUnitTest(QObject* pObject)
{
    CCUnitTestList& list = getUnitTestList();
    if (!findUnitTest(pObject))
    {
        list.append(pObject);
    }
}

/*------------------------------------------------------------------------------------------------------*/
inline int run(int argc, char *argv[])
{
    int nRet = 0;

    foreach (QObject* pTest, getUnitTestList())
    {
        nRet += QTest::qExec(pTest, argc, argv);
    }

    return nRet;
}

/*------------------------------------------------------------------------------------------------------*/
template <class T>
class UnitTestModule
{
public:
    QSharedPointer<T> m_child;

    UnitTestModule(const QString& name) : m_child(new T)
    {
        m_child->setObjectName(name);
        addUnitTest(m_child.data());
    }
};

class CCUnitTest : public QObject
{
};


} // UnitTest
} // CC


#define UNIT_TEST_ADD(className) \
    static CC::UNITTEST::UnitTestModule<className> _TestModule(#className);

/** @}*/

#endif // CCUNITTEST_H
