#include <cstdio>
#include <iostream>
#include <exception>
#include <signal.h>

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

void done() {}

int main(int argc, char * argv[])
{
    // Instantiate the camera interface.
    Camera c;
    
    // Get a frame from the camera.
    const IplImage * pFrame = c.getGreyCameraFrame();

    // Create the dispatcher. Each dispatcher can process a frame one at a time.
    FrameServant dispatcher;
    
    // Create command.
    auto_ptr<ICommand> command; 
    command = auto_ptr<ICommand>((ICommand) new DetectFace(pFrame));

    // Create the proxy.
    FrameProcessor proxy;

    // Execute...
    proxy.Execute(command, dispatcher, done);

    // Get the future object.
    const FaceDetected * pFuture = proxy.GetFuture();


    
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
