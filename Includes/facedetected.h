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

// OS dependencies.
#include <pthread.h>

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
    friend class FrameProcessor;

private:

    // The value.
    bool faceDetected;

    // Mutex for locking data within this object.
    pthread_mutex_t faceDetectedMutex;

private:

    // Hidden copy constructor.
    FaceDetected(const FaceDetected &);

    // Hidden assignment operator.
    FaceDetected & operator= (const FaceDetected &);

    // Sets the value.
    virtual void SetValue(bool detected)
    {
        // Lock the resource.
        pthread_mutex_lock(&faceDetectedMutex);

        // Get the value.
        faceDetected = detected;

        // Unlock the resource.
        pthread_mutex_unlock(&faceDetectedMutex);
    }

public:

    // Constructor.
    FaceDetected() 
    {
        // Create the mutex.
        pthread_mutex_init(&faceDetectedMutex, NULL);

        // Set the value.
        SetValue(false);
    }

    // Destructor.
    virtual ~FaceDetected()
    {
        // Clean up the mutex.
        pthread_mutex_destroy(&faceDetectedMutex);
    }

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
    virtual bool GetValue()
    {
        bool retVal = false;

        // Lock the resource.
        pthread_mutex_lock(&faceDetectedMutex);

        // Get the value.
        retVal = faceDetected;

        // Unlock the resource.
        pthread_mutex_unlock(&faceDetectedMutex);

        return retVal;
    }

};

}

#endif


