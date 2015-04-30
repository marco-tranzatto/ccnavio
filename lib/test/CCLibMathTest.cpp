#include <QtTest/QtTest>

#include <CCUnitTest.h>
#include <CCLibMath.h>
#include <CCPBC.h>

using namespace CC::MATH;
using namespace CC::UNITTEST;

/*------------------------------------------------------------------------------------------------------*/
class CCLibMathTest: public CCUnitTest
{
    Q_OBJECT
private slots:
    void satTest();
    void remapTest();
};

/*------------------------------------------------------------------------------------------------------*/
void CCLibMathTest::satTest()
{
    qint16  nTest          = 0;
    qint16  nTestToPerform = 3;
    qreal   rIn            = 0.0;
    qreal   rLb            = 0.0;
    qreal   rUb            = 0.0;

    for (nTest = 1; nTest <= nTestToPerform; nTest++)
    {
        switch (nTest) {
        case 1:
            rIn            = 0.5;
            rLb            = 0.0;
            rUb            = 1.0;
            QVERIFY(CC::MATH::sat(rIn, rLb, rUb) == 0.5);
            break;

        case 2:
            rIn            = -0.5;
            rLb            = 0.0;
            rUb            = 1.0;
            QVERIFY(CC::MATH::sat(rIn, rLb, rUb) == 0.0);

            break;
        case 3:
            rIn            = 1.5;
            rLb            = 0.0;
            rUb            = 1.0;
            QVERIFY(CC::MATH::sat(rIn, rLb, rUb) == 1.0);
            break;
        default:
            break;
        }
    }

    PBC_INIT
    PBC_VIOLATION_BEGIN
        QVERIFY(sat(nan(), 1.0, 2.0) == 0.0);
    PBC_VIOLATION_END

    QVERIFY(true);
}

/*------------------------------------------------------------------------------------------------------*/
void CCLibMathTest::remapTest()
{
    qint16  nTest          = 0;
    qint16  nTestToPerform = 1;
    qreal   rIn            = 0.0;
    qreal   rXa            = 0.0;
    qreal   rXb            = 0.0;
    qreal   rYa            = 0.0;
    qreal   rYb            = 0.0;

    for (nTest = 1; nTest <= nTestToPerform; nTest++)
    {
        switch (nTest) {
        case 1:
            rIn            =  0.5;
            rXa            =  0.0;
            rXb            =  1.0;
            rYa            = -1.0;
            rYb            =  1.0;
            QVERIFY(CC::MATH::remap(rIn, rXa, rXb, rYa, rYb) == 0.0);
            break;

        default:
            break;
        }
    }
    QVERIFY(true);
}

#include "CCLibMathTest.moc"
UNIT_TEST_ADD(CCLibMathTest)

