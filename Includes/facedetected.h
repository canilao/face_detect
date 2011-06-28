/******************************************************************************/
//
/*! \file

    \brief

    \note

*******************************************************************************/

#ifndef FACEDETECTED_H
#define FACEDETECTED_H

// Standard dependencies.
#include <exception>

// General dependencies.
#include "ifuture.h"

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
 *
*******************************************************************************/
class FaceDetected : ActiveObject::IFuture<bool>
{
private:

    // Hidden copy constructor.
    FaceDetected(const FaceDetected &);

    // Hidden assignment operator.
    FaceDetected & operator= (const FaceDetected &);

public:

    // Constructor.
    FaceDetected() {}

    // Destructor.
    virtual ~FaceDetected() {}

    // Get the search time in milliseconds.
    unsigned int GetSearchTime()
    {
       return 0;
    }

    // Gets the number of objects found in the image. 
    unsigned int GetNumberFacesFound()
    {
       return 0;
    }

    // Gets the value.
    virtual bool GetValue() const
    {
        return false;
    }

};

}

#endif


