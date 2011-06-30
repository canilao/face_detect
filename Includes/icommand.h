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

// OS dependencies.
#include <pthread.h>

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
private:

    // Mutex for locking data within this object.
    pthread_mutex_t iCommandMutex;

protected:

    // Future state callback.
    Ftor::Delegate<void (const FutureState &)> setFutureState;

    // Value callback.
    Ftor::Delegate<void (const std::string &)> setFutureValue;

    // Command done callback.
    Ftor::Delegate<void ()> commandDone;

protected:

    // Sets the future state callback.
    virtual void SetFutureState(const FutureState & fs)
    {
        // Lock the resources.
        pthread_mutex_lock(&iCommandMutex);

        if(setFutureState.IsValid())
        {
            // Save the callback.
            setFutureState(fs);
        }

        // Clean up the mutex.
        pthread_mutex_unlock(&iCommandMutex);
    }

    // Sets the future value callback.
    virtual void SetFutureValue(const std::string & value)
    {
        // Lock the resources.
        pthread_mutex_lock(&iCommandMutex);

        if(setFutureState.IsValid())
        {
            // Save the callback.
            setFutureValue(value);
        }

        // Clean up the mutex.
        pthread_mutex_unlock(&iCommandMutex);
    }

    // Calls back the client signalling the command is complete..
    virtual void CommandDone()
    {
        // Lock the resources.
        pthread_mutex_lock(&iCommandMutex);

        if(setFutureState.IsValid())
        {
            // Save the callback.
            commandDone();
        }

        // Clean up the mutex.
        pthread_mutex_unlock(&iCommandMutex);
    }
public:

    // Constructor.
    ICommand()
    {
        // Initialize the mutex.
        pthread_mutex_init(&iCommandMutex, NULL);
    }

    // Destructor.
    virtual ~ICommand()
    {
        // Clean up the mutex.
        pthread_mutex_destroy(&iCommandMutex);
    }

    // Execute command.
    virtual void Execute() = 0;

    // Cancel the command.
    virtual void Cancel() = 0;

    // Sets the future state callback.
    virtual void SetStateCallback(Ftor::Delegate<void (const FutureState &)> cb)
    {
        // Lock the resources.
        pthread_mutex_lock(&iCommandMutex);

        // Save the callback.
        setFutureState += cb;

        // Clean up the mutex.
        pthread_mutex_unlock(&iCommandMutex);
    }

    // Sets the value callback.
    virtual void SetValueCallback(Ftor::Delegate<void (const std::string &)> cb)
    {
        // Lock the resources.
        pthread_mutex_lock(&iCommandMutex);

        // Save the callback.
        setFutureValue += cb;

        // Clean up the mutex.
        pthread_mutex_unlock(&iCommandMutex);
    }

    // Sets the value callback.
    virtual void SetDoneCallback(Ftor::Delegate<void ()> cb)
    {
        // Lock the resources.
        pthread_mutex_lock(&iCommandMutex);

        // Save the callback.
        commandDone += cb;

        // Clean up the mutex.
        pthread_mutex_unlock(&iCommandMutex);
    }

};

}

#endif
