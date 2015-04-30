#include <CCPBC.h>
#include <QDebug>
#include <QString>

/*------------------------------------------------------------------------------------------------------*/
/*
    Global variable used to capture a PBC exception
*/
/*------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------*/
qbool               PBC_EXCEPTION_TRIGGER   = true;
qbool               PBC_ENABLE_MSG          = true;
CCPBCEventHandler_t CCPBCEventHandler       = CCPBCEventHandlerDefault;
/*------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------*/
void CCPBCEventHandlerReset()
{
    CCPBCEventHandler        = CCPBCEventHandlerDefault;
}

/*------------------------------------------------------------------------------------------------------*/
void CCPBCEventHandlerSet(
        CCPBCEventHandler_t EventHandler
)
{
    PBC_INIT
    PBC_PRECOND(EventHandler != NULL) { return; }
    CCPBCEventHandler        = EventHandler;
}

/*------------------------------------------------------------------------------------------------------*/
void CCPBCEventHandlerDefault(
        QString& PBC_MESSAGE
)
{
    PBC_EXCL_START();
    if (PBC_ENABLE_MSG)
    {
        qDebug() << PBC_MESSAGE;
    }
    PBC_EXCL_STOP();
}
