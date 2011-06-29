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
    const std::auto_ptr<FUTURE_TYPE> & GetFuture() const
    {
        // Throw an error if the future object is asked for too soon.
        if(future.get() == NULL) throw FaceDetect::FutureRequestedTooSoon();

        // Return the future object.
        return future;
    }

};

}

#endif
