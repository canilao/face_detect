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
#include <pthread.h>

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
private:

    // Mutex for locking data within this object.
    pthread_mutex_t dispatcherMutex;

    // Thread that belongs to this object.
    pthread_t dispatcherThread;

    // Flag that keeps the thread running.
    bool keepRunning;

protected:

    // Static entry point for threads.
    static void * ThreadEntry(void * ptr)
    {
        // Cast the pointer.
        IDispatcher * pHost = reinterpret_cast<IDispatcher *>(ptr);

        // Execute the commands.
        pHost->Execute();
    }

    // The thread...
    void Execute()
    {
        bool localExitFlag = true;

        // We are going to hit the workQueue, lock the resource.
        pthread_mutex_lock(&dispatcherMutex);

        // Save the value in a local boolean.
        localExitFlag = keepRunning;

        // We are done modifying the queue, unlock the resource.
        pthread_mutex_unlock(&dispatcherMutex);

        while(localExitFlag)
        {
            ActiveObject::ICommand * pCommand = NULL;

            // We are going to hit the workQueue, lock the resource.
            pthread_mutex_lock(&dispatcherMutex);

            // If the the queue is not empty.
            if(!IsWorkQueueEmpty())
            {
                // Get the next (oldest) command from the queue.
                pCommand = PopNextCommand();
            }

            // We are done modifying the queue, unlock the resource.
            pthread_mutex_unlock(&dispatcherMutex);

            // If we were able to get a pCommand pointer then execute.
            if(pCommand != NULL)
            {
                // Do some work...
                pCommand->Execute();

                // Clean up the pointer.
                delete pCommand;
            }

            // Sleep for 100 ms.
            usleep(1000 * 100);

            // Lock the resource.
            pthread_mutex_lock(&dispatcherMutex);

            // Again save the flag in a local variable.
            localExitFlag = keepRunning;

            // Unlock the resource.
            pthread_mutex_unlock(&dispatcherMutex);
        }
    }

    // Check to see if the work queue is empty.
    virtual bool IsWorkQueueEmpty() = 0;

    // Get the next command.
    virtual ICommand * PopNextCommand() = 0;

public:

    // Constructor.
    IDispatcher() : keepRunning(true)
    {
        pthread_mutex_init(&dispatcherMutex, NULL);
    }

    // Destructor.
    virtual ~IDispatcher()
    {
        // Clean up the mutex.
        pthread_mutex_destroy(&dispatcherMutex);
    }

    // Starts the dispatcher thread.
    void Start()
    {
        // Lock the resource.
        pthread_mutex_lock(&dispatcherMutex);

        // Make sure the flag is set.
        keepRunning = true;

        // Unlock the resource.
        pthread_mutex_unlock(&dispatcherMutex);

        // Create the thread.
        pthread_create(&dispatcherThread, NULL, &IDispatcher::ThreadEntry, (void *) this);
    }

    // Stops the dispatcher thread.
    void Stop()
    {
        // We are going to hit the workQueue, lock the resource.
        pthread_mutex_lock(&dispatcherMutex);

        // This will kill the thread.
        keepRunning = false;

        // We are done modifying the queue, unlock the resource.
        pthread_mutex_unlock(&dispatcherMutex);

        // Join the thread.
        pthread_join(dispatcherThread, NULL);
    }

    // Dispatches a command to the queue.
    virtual void Dispatch(std::auto_ptr<ICommand> cmd) = 0;

    // Check how much work this dispatcher has to do.
    virtual size_t GetSizeOfQueue() = 0;

    // Clears out the work queue. 
    virtual void ClearWorkQueue() = 0;
};

}

#endif
