/******************************************************************************/
//
/*! \file

    \brief

    \note

*******************************************************************************/

#ifndef DETECTFACE_H
#define DETECTFACE_H

// Standard dependencies.
#include <string>

// OS dependencies.
#include <pthread.h>

// General dependencies.
#include "cv.h"
#include "myexceptions.h"

/******************************************************************************/
//
/*! \namespace

    \brief

*******************************************************************************/
namespace FaceDetect
{
/******************************************************************************/
//
/*! \function   CreateFaceCascade

    \brief      This pointer must be released by the client.

*******************************************************************************/
CvHaarClassifierCascade * CreateFaceCascade()
{
    // Haar Cascade file, used for Face Detection.
    std::string faceCascadeFilename = "haarcascade_frontalface_alt.xml";

    // Return value.
    CvHaarClassifierCascade * faceCascade = NULL;

    // Load the HaarCascade classifier for face detection.
    faceCascade = (CvHaarClassifierCascade *)cvLoad(faceCascadeFilename.c_str(),
                  0,
                  0,
                  0);

    // Throw an exception if we fail.
    if(!faceCascade) throw LoadFaceDetectorFailed();

    // Return the pointer.
    return faceCascade;
}

/******************************************************************************/
//
/*! \class

    \brief

*******************************************************************************/
class DetectFace : public ActiveObject::ICommand
{
private:

    // Mutex for locking data within this object.
    pthread_mutex_t detectFaceMutex;

    // Face detector classifier cascade.
    CvHaarClassifierCascade * faceCascade;

    // The image.
    IplImage * inputImage;

private:

    // Hidden copy constructor.
    DetectFace(const DetectFace &);

    // Hidden assignment operator.
    DetectFace & operator= (const DetectFace &);

public:

    // Constructor.
    DetectFace(const IplImage * pOriginal)
    {
        // Initialize the mutex. 
        pthread_mutex_init(&detectFaceMutex, NULL);

        // Lock the resources.
        pthread_mutex_lock(&detectFaceMutex);

        // Clone the image.
        inputImage = cvCloneImage(pOriginal);

        // Get face classifier cascade.
        faceCascade = CreateFaceCascade();

        // We are done modifying resources.
        pthread_mutex_unlock(&detectFaceMutex);
    }

    // Destructor.
    virtual ~DetectFace()
    {
        // Lock the resources.
        pthread_mutex_lock(&detectFaceMutex);

        // Release the face detector.
        cvReleaseHaarClassifierCascade(&faceCascade);

        // Release the image.
        cvReleaseImage(&inputImage);

        // We are done modifying resources.
        pthread_mutex_unlock(&detectFaceMutex);

        // Clean up the mutex.
        pthread_mutex_destroy(&detectFaceMutex);
    }

    // Execute command.
    virtual void Execute()
    {
        // Lock the resources.
        pthread_mutex_lock(&detectFaceMutex);

        // Smallest face size.
        CvSize minFeatureSize = cvSize(20, 20);

        // Only search for 1 face.
        int flags = CV_HAAR_FIND_BIGGEST_OBJECT |
                    CV_HAAR_DO_ROUGH_SEARCH |
                    CV_HAAR_DO_CANNY_PRUNING;

        // How detailed should the search be.
        float search_scale_factor = 1.1f;
        IplImage * detectImg;
        IplImage * greyImg = 0;
        CvMemStorage * storage;
        CvRect rc;
        double t;
        CvSeq * rects;
        CvSize size;
        int ms, nFaces;

        storage = cvCreateMemStorage(0);
        cvClearMemStorage(storage);

        // If the image is color, use a greyscale copy of the image.
        detectImg = (IplImage *)inputImage;

        if(inputImage->nChannels > 1)
        {
            size = cvSize(inputImage->width, inputImage->height);
            greyImg = cvCreateImage(size, IPL_DEPTH_8U, 1);
            cvCvtColor(inputImage, greyImg, CV_BGR2GRAY);

            // Use the greyscale image.
            detectImg = greyImg;
        }

        // Detect all the faces in the greyscale image.
        t = (double)cvGetTickCount();

        rects = cvHaarDetectObjects(detectImg,
                                    faceCascade,
                                    storage,
                                    search_scale_factor,
                                    3,
                                    flags,
                                    minFeatureSize);

        t = (double)cvGetTickCount() - t;

        ms = cvRound(t / ((double)cvGetTickFrequency() * 1000.0));

        nFaces = rects->total;
        printf("Face Detection took %d ms and found %d objects\n", ms, nFaces);

        // Get the first detected face (the biggest).
        if(nFaces > 0)
        {
            rc = *(CvRect *)cvGetSeqElem(rects, 0);
        }
        else
        {
            // Couldn't find the face.
            rc = cvRect(-1,-1,-1,-1);
        }

        if(greyImg) cvReleaseImage(&greyImg);

        cvReleaseMemStorage(&storage);

        // We are done modifying resources.
        pthread_mutex_unlock(&detectFaceMutex);
    }

};

}

#endif


