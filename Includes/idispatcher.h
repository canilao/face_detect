/******************************************************************************/
//
/*! \file

    \brief

    \note

*******************************************************************************/

#ifndef DISPATHER_OBJECT_H
#define DISPATHER_OBJECT_H

// Standard dependencies.
#include <memory>

// General dependencies.
#include "icommand.h"

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
class IDispatcher
{
public:

    // Constructor.
    IDispatcher() {}

    // Destructor.
    virtual ~IDispatcher() {}

    // Starts the dispatcher thread.
    virtual void Start() = 0;

    // Stops the dispatcher thread.
    virtual void Stops() = 0;

    // Dispatches an command to the queue.
    virtual void Dispatch(std::auto_ptr<ICommand> cmd) = 0;

};

}

#endif
