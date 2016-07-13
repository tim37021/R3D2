#include <R3D/R3D.h>
#include <cstdio>

using namespace r3d;

using namespace core;

Device *device=nullptr;

int main(int argc, char *argv[])
{
    device = CreateDevice(Vector2i(800, 600), "R3D Engine 2.0");
    char buf[128];
    int fps=0;
    double lastTime=device->getTime();

    TaskScheduler *ts = device->getTaskScheduler();

    while(device->isRunning()) {
        
        device->pollEvents();
        device->swapBuffers();

        fps++;
        if(device->getTime() - lastTime>1.0) {
            sprintf(buf, "R3D Engine 2.0 - %d fps", fps);
            device->setWindowCaption(buf);
            fps=0;
            lastTime = device->getTime();
        }
    }
    
    DestroyDevice(device);
    return 0;
}