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
    command = auto_ptr<ICommand>((ICommand *) new DetectFace(pFrame));

    // Create the proxy.
    FrameProcessor proxy;

    // Execute...
    proxy.Execute(command, dispatcher, done);

    try
    {
       // Get the future object.
       const FaceDetected * pFuture = proxy.GetFuture();
    }
    catch(...)  {}

    return 0;
}
