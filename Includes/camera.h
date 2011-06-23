/******************************************************************************/
//
/*! \file

    \brief

    \note

*******************************************************************************/

#ifndef CAMERA_H
#define CAMERA_H

// Standard dependencies.
#include <exception>

// General dependencies.
#include "cv.h"
#include "highgui.h"
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
class Camera
{
private:

    // Pointer the camera.
    CvCapture * pCamera;

private:

    // Hidden copy constructor.
    Camera(const Camera &);

    // Hidden assignment operator.
    Camera & operator= (const Camera &);

public:

    // Constructor.
    Camera()
    {
        pCamera = cvCaptureFromCAM(0);

        // Initialize the camera.
        cvQueryFrame(pCamera);
    }

    // Destructor.
    virtual ~Camera()
    {
        cvReleaseCapture(&pCamera);
    }

    // Expose the internal CvCapture pointer.
    CvCapture & getCamera()
    {
        return *pCamera;
    }

    // Gets the current frame.
    const IplImage * getCameraFrame()
    {
        const int grab_loops = 4;

        // Clear out the buffer so we can get a recent frame.
        for(int i = 0 ; i < grab_loops ; ++i)
        {
            cvGrabFrame(pCamera);
        }

        return cvQueryFrame(pCamera);
    }

    // Get the current frame but greyscale.
    const IplImage * getGreyCameraFrame()
    {
        IplImage * imageGrey;

        // Get the camera frame.
        const IplImage * imageSrc = getCameraFrame();

        // Either convert the image to greyscale, or make a copy of the existing
        // greyscale image. This is to make sure that the user can always call
        // cvReleaseImage() on the output, whether it was greyscale or not.
        if(imageSrc->nChannels == 3)
        {
            imageGrey = cvCreateImage(cvGetSize(imageSrc), IPL_DEPTH_8U, 1);
            cvCvtColor(imageSrc, imageGrey, CV_BGR2GRAY);
        }
        else
        {
            imageGrey = cvCloneImage(imageSrc);
        }

        return imageGrey;
    }

};

}

#endif


