#ifndef CCPBC_H
#define CCPBC_H

/*------------------------------------------------------------------------------------------------------*/
/**
 * \file:       CCPBC.h
 * \brief       Programming by Contract
 *              Library of MACROS used to robustify the code with the
 *              PBC approach.
 *              http://en.wikipedia.org/wiki/Design_by_contract
 *
 * \author:     Vincenzo Calabrò <vincenzo@calabrothers.com>
 *
 * \defgroup    PBC Programming By Contract
 * \ingroup     CCLibrary
 */

#include <CCTypes.h>
#include <QString>
#include <assert.h>

/*------------------------------------------------------------------------------------------------------*/
/** \addtogroup PBC
 *  @{
 */

/*------------------------------------------------------------------------------------------------------*/
/**
 * \brief       Function Event Handler Type
*/
typedef void (*CCPBCEventHandler_t)(QString&);

/*------------------------------------------------------------------------------------------------------*/
extern qbool                PBC_EXCEPTION_TRIGGER;  /**< To capture expected
                                                            violations                                  */
extern qbool                PBC_ENABLE_MSG;         /**< To disable printouts                           */
extern CCPBCEventHandler_t  CCPBCEventHandler;      /**< Event Handler                                  */

/*------------------------------------------------------------------------------------------------------*/
/**
 * \brief       Default Event Handler for a PBC event
*/
void CCPBCEventHandlerDefault(
        QString& PBC_MESSAGE                        /**< I: Message to propagate                        */
);

/*------------------------------------------------------------------------------------------------------*/
/**
 * \brief       Reset Default Event Handler for a PBC event
*/
void CCPBCEventHandlerReset();

/*------------------------------------------------------------------------------------------------------*/
/**
 * \brief       Change Event Handler for a PBC event
*/
void CCPBCEventHandlerSet(
        CCPBCEventHandler_t EventHandler            /**< I: Message to propagate                        */
);

/*------------------------------------------------------------------------------------------------------*/
/* Programming By Contract                                                                              */
/* Macros used to identify anomalies in the code                                                        */
/*------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------*/
/**
 * \brief       Function used to deliver the PBC message
*/
#define PBC_VIOLATION_EVENT(...) \
        PBC_MESSAGE.sprintf(__VA_ARGS__); \
        CCPBCEventHandler(PBC_MESSAGE);

/*------------------------------------------------------------------------------------------------------*/
/**
 * \brief       Function used to initialize the PBC system
*/
#define PBC_INIT \
        qbool    PBC_VIOLATION  = false; \
        QString  PBC_MESSAGE;

/*------------------------------------------------------------------------------------------------------*/
/**
 * \brief       Function used to request a violation
*/
#define PBC_VIOLATION_BEGIN \
        PBC_EXCEPTION_TRIGGER   = false;\
        PBC_ENABLE_MSG          = false;

/*------------------------------------------------------------------------------------------------------*/
/**
 * \brief       Function used to perform a general check
*/
#define PBC_CONDITION(C, TYPE) \
        PBC_VIOLATION   = !(C); \
        if (PBC_VIOLATION == true) { \
            PBC_EXCEPTION_TRIGGER  = true; \
            PBC_VIOLATION_EVENT("PBC: "#TYPE": ("#C") Error at %s, line %d.",  __FILE__, __LINE__); \
        }\
        if (PBC_VIOLATION == true)

/*------------------------------------------------------------------------------------------------------*/
/**
 * \brief       Function used to conclude a violation
*/
#define PBC_VIOLATION_END \
        PBC_ENABLE_MSG        = true;\
        PBC_CONDITION(PBC_EXCEPTION_TRIGGER == true, Violation Fail){ QVERIFY(false); }\
        PBC_EXCEPTION_TRIGGER = false;

/*------------------------------------------------------------------------------------------------------*/
/**
 * \brief       Function used to perform a preconditioning check
*/
#define PBC_PRECOND(C)          PBC_CONDITION(C, PRECOND)

/*------------------------------------------------------------------------------------------------------*/
/**
 * \brief       Function used to perform an invariant check
*/
#define PBC_INVARIANT(C)        PBC_CONDITION(C, INVARIANT)

/*------------------------------------------------------------------------------------------------------*/
/**
 * \brief       Function used to perform a postconditioning check
*/
#define PBC_POSTCOND(C)         PBC_CONDITION(C, POSTCOND)

/*------------------------------------------------------------------------------------------------------*/
/**
 * \brief       Macro used to disable code coverage temporarly: begin
*/
#define PBC_EXCL_START()    /*  Exclude the following code: begin   */

/*------------------------------------------------------------------------------------------------------*/
/**
 * \brief       Macro used to disable code coverage temporarly: end
*/
#define PBC_EXCL_STOP()     /*  Exclude the following code: end     */

/*------------------------------------------------------------------------------------------------------*/
/**
 * \brief       Macro used to check the result of a function within tests
*/
#define PBC_ASSERT(C) assert(C);  /*  Check the result is true     */

/** @}*/


#endif // CCPBC_H
