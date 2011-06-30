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
#include <string>

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
class IProxy : public Ftor::ObjectFunctionOwner
{
private:

    // Future object.
    std::auto_ptr<FUTURE_TYPE> future;

protected:

    // Gets a modifiable future pointer.
    std::auto_ptr<FUTURE_TYPE> & GetModifiableFutureObj()
    {
        return future;
    }

    // Callback for signaling what state the future object should be.
    virtual void FutureStateCallback(const FutureState & futureState) = 0;

    // Callback for signaling back the value.
    virtual void FutureValueCallback(const std::string & value) = 0;

public:

    // Constructor.
    IProxy()
    {
        future = std::auto_ptr<FUTURE_TYPE>(new FUTURE_TYPE());
    }

    // Destructor.
    virtual ~IProxy() {}

    // Executes an operation.
    virtual const std::auto_ptr<FUTURE_TYPE> & Execute(std::auto_ptr<ICommand> cmd,
                                                       IDispatcher & disp,
                                                       Ftor::Delegate<void ()> doneCallback)
    {
        // Create a new future object.
        future = std::auto_ptr<FUTURE_TYPE>(new FUTURE_TYPE());

        // Setup the future state callback.
        Ftor::Delegate<void (const FutureState &)> fscb(this, &IProxy::FutureStateCallback);
        cmd->SetStateCallback(fscb);

        // Setup the value callback.
        Ftor::Delegate<void (const std::string &)> vcb(this, &IProxy::FutureValueCallback);
        cmd->SetValueCallback(vcb);

        // Save the done call back.
        cmd->SetDoneCallback(doneCallback);

        // Save the command in the dispatcher.
        disp.Dispatch(cmd);

        return future;
    }

    // Cancels the job.
    virtual void Cancel()
    {
        // Cancel the current job.
    }

};

}

#endif
