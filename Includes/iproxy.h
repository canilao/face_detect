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
    FUTURE_TYPE * future;

protected:
    
    // Callback for signaling what state the future object should be. 
    virtual void FutureStateCallback(const FutureState & futureState)
    {
       // Set the future state in the IFuture object.
    }

    // Callback for signaling back the value. 
    virtual void FutureValueCallback(const std::string & value)
    {
       // Set the value in the IFuture object.
    }

public:

    // Constructor.
    IProxy() : future(NULL) {}

    // Destructor.
    virtual ~IProxy() {}

    // Executes an operation.
    virtual void Execute(std::auto_ptr<ICommand> cmd,
                         IDispatcher & disp,
                         Ftor::Delegate<void ()> doneCallback)
    {
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
    }

    // Cancels the job.
    virtual void Cancel()
    {
       // Cancel the current job.
    }

    // Gets a reference to the future object.
    const FUTURE_TYPE * GetFuture() const
    {
        if(future == NULL) throw FaceDetect::FutureRequestedTooSoon();

        return future;
    }

};

}

#endif
