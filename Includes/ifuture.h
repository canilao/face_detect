/******************************************************************************/
//
/*! \file   ifuture.h

    \brief

    \note

*******************************************************************************/

#ifndef FUTURE_OBJECT_H
#define FUTURE_OBJECT_H

// Standard dependencies.

// General dependencies.

/******************************************************************************/
//
/*! \namespace

    \brief

*******************************************************************************/
namespace ActiveObject
{
/******************************************************************************/
//
/*! \enum   FutureState

    \brief

*******************************************************************************/
enum FutureState
{
    // This means the work is in progress.
    Pending,

    // The work is complete and we are waiting for the value.
    Succeeded,

    // The work failed.
    Failed,

    // The work is in the process of being cancelled.
    Cancelling,

    // The work was cancelled by the client.
    Cancelled,

    // The value is ready for the client.
    HasValue
};

/******************************************************************************/
//
/*! \class  IFuture

    \brief  Future object interface.

*******************************************************************************/
template<class RETURN_TYPE>
class IFuture
{
private:

    // Hidden copy constructor.
    IFuture(const IFuture &);

    // Hidden assignment operator.
    IFuture & operator= (const IFuture &);

private:

    // Mutex for locking data within this object.
    pthread_mutex_t iFutureMutex;

    // The state of the future object.
    FutureState state;

protected:

    // Sets the state of the future object.
    void SetFutureState(FutureState newState)
    {
        // Lock the resource.
        pthread_mutex_lock(&iFutureMutex);

        // Get the value.
        state = newState;

        // Unlock the resource.
        pthread_mutex_unlock(&iFutureMutex);
    }

    // How the value is set.
    virtual void SetValue(RETURN_TYPE detected) = 0;

public:

    // Constructor.
    IFuture()
    {
        // Create the mutex.
        pthread_mutex_init(&iFutureMutex, NULL);
    }

    // Destructor.
    virtual ~IFuture()
    {
        // Clean up the mutex.
        pthread_mutex_destroy(&iFutureMutex);
    }

    // Queries if the future objects state.
    FutureState GetState() const
    {
        return state;
    }

    // Gets the value.
    virtual RETURN_TYPE GetValue() = 0;

};

}

#endif
