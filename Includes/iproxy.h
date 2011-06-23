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
template<class RETURN_TYPE>
class IProxy
{
private:

    // Future object.
    std::auto_ptr<IFuture<RETURN_TYPE> > future;

public:

    // Constructor.
    IProxy() {}

    // Destructor.
    virtual ~IProxy() {}

    // Executes an operation.
    virtual void Execute(std::auto_ptr<ICommand> cmd, 
                         IDispatcher & disp,
                         Ftor::Delegate<void ()> doneCallback) = 0;

    // Cancels the job.
    virtual void Cancel() = 0;

    // Gets a reference to the future object.
    const std::auto_ptr<IFuture<RETURN_TYPE> > & GetFuture() const
    {
        return future;
    }

};

}

#endif
