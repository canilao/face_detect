#include <cstdio>
#include <iostream>
#include <exception>
#include <signal.h>
#include <vector>

#include "camera.h"
#include "frameservant.h"
#include "frameprocessor.h"
#include "detectface.h"
#include "ftor.h"
#include "iproxy.h"
#include "icommand.h"

#include "cv.h"
#include "highgui.h"

using namespace std;
using namespace FaceDetect;
using namespace ActiveObject;

void DoneFunc() {}

int main(int argc, char * argv[])
{
    // Number of servants.
    const int NUM_SERVANTS = 5;

    // Time out value
    const int TIMEOUT = 500;

    // Instantiate the camera interface.
    Camera cam;

    // Create 5 servants.
    vector<FrameServant> servants(NUM_SERVANTS);

    // Start the threads in the servants.
    for(vector<FrameServant>::iterator iter = servants.begin() ;
            iter != servants.end() ;
            ++iter)
    {
        (*iter).Start();
    }


    while(true)
    {
        // Get a frame from the camera.
        const IplImage * pFrame = cam.getGreyCameraFrame();

        // Will hold the servant with the least amount of work.
        vector<FrameServant>::iterator freeIterServant = servants.begin();

        // Find a servant that has the least to do.
        for(vector<FrameServant>::iterator iter = servants.begin() ;
                iter != servants.end() ;
                ++iter)
        {
            size_t sizeCurrent = (*iter).GetSizeOfQueue();

            if(sizeCurrent < (*freeIterServant).GetSizeOfQueue())
            {
                freeIterServant = iter;
            }
        }

        // Create command.
        auto_ptr<ICommand> command;
        command = auto_ptr<ICommand>((ICommand *) new DetectFace(pFrame));

        // Create the proxy.
        FrameProcessor proxy;

        // Execute...
        proxy.Execute(command,*freeIterServant, DoneFunc);

        // Get the start time.
        double t = (double)cvGetTickCount();

        // Every 50ms, check to see if we are done.
        while(true)
        {
            // How much time has passed in milliseconds.
            t = (double)cvGetTickCount() - t;
            int ms = cvRound(t / ((double)cvGetTickFrequency() * 1000.0));

            if(proxy.GetFuture()->GetState() == ActiveObject::HasValue ||
                    ms > TIMEOUT)
            {
                break;
            }

            usleep(1000 * 50);
        }

        if(proxy.GetFuture()->GetState() != ActiveObject::HasValue)
        {
            cout << "Face NOT detected" << endl;
        }
        else if(!proxy.GetFuture()->GetValue().faceDetected)
        {
            cout << "Face NOT detected" << endl;
        }
        else if(proxy.GetFuture()->GetValue().faceDetected)
        {
            cout << "I see you!!!!!!!" << endl;
        }
        else
        {
            cout << "Unknown behavior" << endl;
        }
    }

    return 0;
}
