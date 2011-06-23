/******************************************************************************/
//
/*! \file   ifuture.h

    \brief

    \note

*******************************************************************************/

#ifndef FUTURE_OBJECT_H
#define FUTURE_OBJECT_H

// Standard dependencies.
#include <exception>

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

    // The state of the future object.
    FutureState state;

public:

    // Constructor.
    IFuture()
    {
    }

    // Destructor.
    virtual ~IFuture()
    {
    }

    // Queries if the future objects state.
    FutureState GetState() const
    {
        return state;
    }

    // Gets the value.
    virtual RETURN_TYPE GetValue() const = 0;

    // Gets the error.
    virtual const std::exception & GetError() const = 0;

};

}

#endif
