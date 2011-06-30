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
/*! \struct

    \brief
 *
*******************************************************************************/
struct FaceDetectionData
{
    // Whether or not a face was detected.
    bool faceDetected;

    // How long it took to detect the face in milliseconds.
    unsigned int detectionTime;

    // Number of objects found.
    unsigned int numberFacesFound;
};

/******************************************************************************/
//
/*! \class

    \brief
 *
*******************************************************************************/
class FaceDetected : public ActiveObject::IFuture<FaceDetectionData>
{
    friend class FrameProcessor;

private:

    // The value.
    FaceDetectionData faceDetected;

    // Mutex for locking data within this object.
    pthread_mutex_t faceDetectedMutex;

private:

    // Hidden copy constructor.
    FaceDetected(const FaceDetected &);

    // Hidden assignment operator.
    FaceDetected & operator= (const FaceDetected &);

    // Sets the value.
    virtual void SetValue(FaceDetectionData detected)
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

        // Create some initial data.
        FaceDetectionData fdd;
        fdd.faceDetected = false;
        fdd.detectionTime = 0;
        fdd.numberFacesFound = 0;

        // Set the value.
        SetValue(fdd);
    }

    // Destructor.
    virtual ~FaceDetected()
    {
        // Clean up the mutex.
        pthread_mutex_destroy(&faceDetectedMutex);
    }

    // Gets the value.
    virtual FaceDetectionData GetValue()
    {
        FaceDetectionData retVal;

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


