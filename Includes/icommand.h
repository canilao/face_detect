/******************************************************************************/
//
/*! \file

    \brief

    \note

*******************************************************************************/

#ifndef COMMAND_OBJECT_H
#define COMMAND_OBJECT_H

// Standard dependencies.
#include <string>
#include <exception>

// General dependencies.
#include "ftor.h"

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
class ICommand
{
public:

    // Constructor.
    ICommand() {}

    // Destructor.
    virtual ~ICommand() {}

    // Execute command.
    virtual void Execute() = 0;

    // Sets the future state callback.
    virtual void SetStateCallback(Ftor::Delegate<void (const FutureState &)> cb) = 0;

    // Sets the value callback.
    virtual void SetValueCallback(Ftor::Delegate<void (const std::string &)> cb) = 0;

    // Sets the value callback.
    virtual void SetDoneCallback(Ftor::Delegate<void ()> cb) = 0;

};

}

#endif
