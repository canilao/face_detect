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
protected:

    // Callback for signaling what state the future object should be.
    virtual void FutureStateCallback(const ActiveObject::FutureState & futureState)
    {
        // Set the future state.
        GetModifiableFutureObj()->SetFutureState(futureState);
    }

    // Callback for signaling back the value.
    virtual void FutureValueCallback(const std::string & value)
    {
        if(value == "True")
        {
            GetModifiableFutureObj()->SetValue(true);
        }
        else if(value == "False")
        {
            GetModifiableFutureObj()->SetValue(false);
        }
        else
        {
            throw InvalidFutureValue();
        }

    }

public:

    // Constructor.
    FrameProcessor() {}

    // Destructor.
    virtual ~FrameProcessor() {}

};

}

#endif


