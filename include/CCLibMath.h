#ifndef CCLIBMATH_H
#define CCLIBMATH_H

/*------------------------------------------------------------------------------------------------------*/
/**
 * \file:       CCLibMath.h
 * \brief       Basic Math Library
 *
 * \author:     Vincenzo Calabrò <vincenzo@calabrothers.com>
 *
 * \defgroup    MATH Math Library
 * \ingroup     CCLibrary
 */

#include <CCTypes.h>

using namespace arma;

/*------------------------------------------------------------------------------------------------------*/
/** \addtogroup MATH
 *  @{
 */

namespace CC {
namespace MATH {

/*------------------------------------------------------------------------------------------------------*/
inline qbool isNum(qreal rValue) {
    return (is_finite(rValue));
}

/*------------------------------------------------------------------------------------------------------*/
inline qreal nan()
{
    return datum::nan;
}

/*------------------------------------------------------------------------------------------------------*/
qreal sat(const qreal& rIn,
          const qreal& rLb,
          const qreal& rUb);

/*------------------------------------------------------------------------------------------------------*/
qreal remap(const qreal& rX,
            const qreal& rXa,
            const qreal& rXb,
            const qreal& rYa,
            const qreal& rYb);

} // Math
} // CC

/** @}*/

#endif // CCLIBMATH_H
