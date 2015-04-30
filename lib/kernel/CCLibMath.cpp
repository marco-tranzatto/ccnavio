#include <CCLibMath.h>
#include <CCPBC.h>

/*------------------------------------------------------------------------------------------------------*/
qreal CC::MATH::sat(const qreal &rIn,
                    const qreal &rLb,
                    const qreal &rUb)
{
    qreal rValueOut = 0.0;

    PBC_INIT
    PBC_PRECOND(isNum(rIn))                     {   return  0.0; }
    PBC_PRECOND(isNum(rLb))                     {   return  0.0; }
    PBC_PRECOND(isNum(rUb))                     {   return  0.0; }

    /* Perform saturation of input value                                    */
    rValueOut     = rIn;

    if (rIn > rUb) {
        rValueOut     = rUb;
    }

    if (rIn < rLb) {
        rValueOut     = rLb;
    }

    return rValueOut;
}

/*------------------------------------------------------------------------------------------------------*/
qreal CC::MATH::remap(const qreal &rX,
                      const qreal &rXa,
                      const qreal &rXb,
                      const qreal &rYa,
                      const qreal &rYb)
{
    qreal rValueOut = 0.0;

    PBC_INIT
    PBC_PRECOND(isNum(rX))                      {   return  0.0; }
    PBC_PRECOND(isNum(rXa))                     {   return  0.0; }
    PBC_PRECOND(isNum(rXb))                     {   return  0.0; }
    PBC_PRECOND(isNum(rYa))                     {   return  0.0; }
    PBC_PRECOND(isNum(rYb))                     {   return  0.0; }

    rValueOut = rYa + (rYb-rYa)/(rXb-rXa)*(rX-rXa);
    return rValueOut;
}
