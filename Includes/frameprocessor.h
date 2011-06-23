/******************************************************************************/
//
/*! \file

    \brief

    \note

*******************************************************************************/

#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H

// Standard dependencies.
#include <memory>

// General dependencies.
#include "ftor.h"
#include "iproxy.h"
#include "ifuture.h"
#include "icommand.h"

/******************************************************************************/
//
/*! \namespace

    \brief

*******************************************************************************/
namespace FaceDetect
{
/******************************************************************************/
//
/*! \class

    \brief

*******************************************************************************/
class FrameProcessor : public ActiveObject::IProxy<FaceDetected>
{
public:

    // Constructor.
    FrameProcessor() {}

    // Destructor.
    virtual ~FrameProcessor() {}

    // Executes an operation.
    virtual void Execute(ActiveObject::ICommand * cmd,
                         ActiveObject::IDispatcher & disp,
                         Ftor::Delegate<void ()> doneCallback) {}

    // Cancels the job.
    virtual void Cancel() {}

};

}

#endif


