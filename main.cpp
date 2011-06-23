#include <cstdio>
#include <iostream>
#include <exception>
#include <signal.h>

#include "cv.h"
#include "highgui.h"

#include "ftor.h"
#include "iproxy.h"
#include "icommand.h"

using namespace std;

class pthread_create_failed : public exception
{
    virtual const char * what() const throw()
    {
        return "pthread_create failed";
    }
};

class load_face_detector_failed : public exception
{
    virtual const char * what() const throw()
    {
        return "face detector failed to load ";
    }
};

class camera
{
private:

    // Pointer the camera.
    CvCapture * pCamera;

private:

    // Hidden copy constructor.
    camera(const camera &);

    // Hidden assignment operator.
    camera & operator= (const camera &);

public:

    // Constructor.
    camera()
    {
        pCamera = cvCaptureFromCAM(0);

        // Initialize the camera.
        cvQueryFrame(pCamera);
    }

    // Destructor.
    virtual ~camera()
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

class face_detector
{
private:

    // Face detector.
    CvHaarClassifierCascade * faceCascade;

    // The image.
    IplImage * inputImage;

private:

    // Hidden copy constructor.
    face_detector(const face_detector &);

    // Hidden assignment operator.
    face_detector & operator= (const face_detector &);

public:

    // Constructor.
    face_detector(IplImage * img)
    {
        // Save the input image.
        inputImage = img;

        // Haar Cascade file, used for Face Detection.
        string faceCascadeFilename = "haarcascade_frontalface_alt.xml";

        // Load the HaarCascade classifier for face detection.
        faceCascade = (CvHaarClassifierCascade *)cvLoad(faceCascadeFilename.c_str(),
                      0,
                      0,
                      0);

        // Throw an exception if we fail.
        if(!faceCascade) throw load_face_detector_failed();
    }

    // Destructor.
    virtual ~face_detector()
    {
        // Release the face detector.
        cvReleaseHaarClassifierCascade(&faceCascade);

        // Release the image.
        cvReleaseImage(&inputImage);
    }

    // Execute face detection.
    void executeDetection()
    {
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
    }

};

int main(int argc, char * argv[])
{
    /*
    const int NUM_THREADS = 15;

    pthread_t threads[NUM_THREADS];
    int rc, i;

    while(true)
    {
       // Go through the threads and see if it is alive.
       for(int i = 0 ; i < NUM_THREADS ; ++i)
       {
          // Is the thread running...
          if(pthread_kill(threads[i], 0) != 0)
          {
             // Not running...

             // Create the thread.
             rc = pthread_create(&threads[i], NULL, Execute, NULL);

             cout << "thread " << i << endl;

             // Throw and exception if we need to.
             if(0 != rc) throw pthread_create_failed();

             // If we are done break
             break;
          }
       }

       sleep(1);
    }
    */

    return 0;
}
