#ifndef CCTYPES_H
#define CCTYPES_H

/*------------------------------------------------------------------------------------------------------*/
/**
 * \file:       CCTypes.h
 * \brief       Definition of basic types (not included into Qt5)
 *
 * \author:     Vincenzo Calabrò <vincenzo@calabrothers.com>
 *
 * \defgroup    TYPES Definition of basic types
 * \ingroup     CCLibrary
 */

#include <QtGlobal>
#include <armadillo>

/*------------------------------------------------------------------------------------------------------*/
/** \addtogroup PBC
 *  @{
 */

/*------------------------------------------------------------------------------------------------------*/
typedef bool                qbool;

/*------------------------------------------------------------------------------------------------------*/
typedef char                qchar;

/*------------------------------------------------------------------------------------------------------*/
typedef arma::Mat<qreal>    qmatrix;

/** @}*/

#endif // CCTYPES_H
