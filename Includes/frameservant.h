/******************************************************************************/
//
/*! \file

    \brief

    \note

*******************************************************************************/

#ifndef FRAMESERVANT_H
#define FRAMESERVANT_H

// Standard dependencies.
#include <queue>

// OS dependencies.
#include <pthread.h>

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
private:

    // Mutex for locking data within this object.
    pthread_mutex_t servantMutex;

    // FrameServant has a FIFO order of operation.
    std::queue<ActiveObject::ICommand *> workQueue;

public:

    // Constructor.
    FrameServant()
    {
        pthread_mutex_init(&servantMutex, NULL);
    }

    // Destructor.
    virtual ~FrameServant()
    {
        // We are going to hit the workQueue, lock the resource.
        pthread_mutex_lock(&servantMutex);

        // Make sure the pointers are cleaned out of the work queue.
        while(!workQueue.empty())
        {
            // Delete the pointer.
            delete workQueue.front();

            // Pop the recently deleted pointer.
            workQueue.pop();
        }

        // We are done modifying the queue, unlock the resource.
        pthread_mutex_unlock(&servantMutex);

        // Clean up the mutex.
        pthread_mutex_destroy(&servantMutex);
    }

    // The thread...
    void DoWork()
    {
        // We are going to hit the workQueue, lock the resource.
        pthread_mutex_lock(&servantMutex);

        // Get the next (oldest) command from the queue.
        ActiveObject::ICommand * pCommand = workQueue.front();

        // Pop the oldest command from the queue.
        workQueue.pop();

        // We are done modifying the queue, unlock the resource.
        pthread_mutex_unlock(&servantMutex);

        // Do some work...
        pCommand->Execute();

        // Write the result to the future object...

        // Clean up the pointer.
        delete pCommand;
    }


    // Starts the dispatcher thread.
    virtual void Start() {}

    // Stop the dispatcher thread.
    virtual void Stop() {}

    // Dispatches an command to the queue.
    virtual void Dispatch(std::auto_ptr<ActiveObject::ICommand> cmd)
    {
        // We are going to hit the workQueue, lock the resource.
        pthread_mutex_lock(&servantMutex);

        // Push the command on to the queue.
        workQueue.push(cmd.release());

        // We are done modifying the queue, unlock the resource.
        pthread_mutex_unlock(&servantMutex);
    }

};

}

#endif




