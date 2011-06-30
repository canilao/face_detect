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
#include <unistd.h>
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

protected:

    // Check to see if the work queue is empty.
    virtual bool IsWorkQueueEmpty()
    {
        bool retVal = false;

        // We are going to hit the workQueue, lock the resource.
        pthread_mutex_lock(&servantMutex);

        // Save the boolean to a local variable.
        retVal = workQueue.empty();

        // We are done modifying the queue, unlock the resource.
        pthread_mutex_unlock(&servantMutex);

        return retVal;
    }

    // Get the next command.
    virtual ActiveObject::ICommand * PopNextCommand()
    {
        ActiveObject::ICommand * pCommand = NULL;

        // We are going to hit the workQueue, lock the resource.
        pthread_mutex_lock(&servantMutex);

        // Get the next (oldest) command from the queue.
        pCommand = workQueue.front();

        // Pop the oldest command from the queue.
        workQueue.pop();

        // We are done modifying the queue, unlock the resource.
        pthread_mutex_unlock(&servantMutex);

        return pCommand;
    }

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

    // Check to see how much work this servant has.
    virtual size_t GetSizeOfQueue()
    {
        size_t retVal = 0;

        // We are going to hit the workQueue, lock the resource.
        pthread_mutex_lock(&servantMutex);

        // Save the boolean to a local variable.
        retVal = workQueue.size();

        // We are done modifying the queue, unlock the resource.
        pthread_mutex_unlock(&servantMutex);

        return retVal;
    }

};

}

#endif




