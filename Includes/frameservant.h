/******************************************************************************/
//
/*! \file

    \brief

    \note

*******************************************************************************/

#ifndef FRAMESERVANT_H
#define FRAMESERVANT_H

// Standard dependencies.

// General dependencies.
#include "idispatcher.h"

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
class FrameServant : public ActiveObject::IDispatcher
{
public:

    // Constructor.
    FrameServant() {}

    // Destructor.
    virtual ~FrameServant() {}

    // Starts the dispatcher thread.
    virtual void Start() { /* Grab the next cmd out of the queue and invoke */ }

    // Stops the dispatcher thread.
    virtual void Stops() {}

    // Dispatches an command to the queue.
    virtual void Dispatch(std::auto_ptr<ActiveObject::ICommand> cmd) {}

};

}

#endif




