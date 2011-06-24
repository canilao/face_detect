/******************************************************************************/
//
/*! \file

    \brief

    \note

*******************************************************************************/

#ifndef PROXY_OBJECT_H
#define PROXY_OBJECT_H

// Standard dependencies.
#include <memory>

// General dependencies.
#include "ftor.h"
#include "ifuture.h"
#include "icommand.h"
#include "idispatcher.h"
#include "facedetected.h"
#include "myexceptions.h"

/******************************************************************************/
//
/*! \namespace

    \brief

*******************************************************************************/
namespace ActiveObject
{
/******************************************************************************/
//
/*! \class

    \brief

*******************************************************************************/
template<class FUTURE_TYPE>
class IProxy
{
private:

    // Future object.
    FUTURE_TYPE * future;

public:

    // Constructor.
    IProxy() : future(NULL) {}

    // Destructor.
    virtual ~IProxy() {}

    // Executes an operation.
    virtual void Execute(std::auto_ptr<ICommand> cmd,
                         IDispatcher & disp,
                         Ftor::Delegate<void ()> doneCallback) = 0;

    // Cancels the job.
    virtual void Cancel() = 0;

    // Gets a reference to the future object.
    const FUTURE_TYPE * GetFuture() const
    {
        if(future == NULL) throw FaceDetect::FutureRequestedTooSoon();

        return future;
    }

};

}

#endif
