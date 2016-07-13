#include <R3D/R3D.h>
#include <cstdio>

using namespace r3d;

using namespace core;
using namespace rendering;

Device *device=nullptr;

class MyFinishTask: public Task
{
public:
    MyFinishTask(): Task(0){}
    virtual ~MyFinishTask()=default;
    virtual void execute()
    {
        fprintf(stderr, "Finish image loading\n");
    }
};

class MyTask: public Task
{
public:
    MyTask(TaskScheduler *t): Task(0), ts(t){}
    virtual ~MyTask()=default;
    virtual void execute()
    {
        image.loadFromFile("test.png");
        ts->scheduleTask(&tfinish);
    }
private:
    TaskScheduler *ts;
    MyFinishTask tfinish;
    Image image;
};

int main(int argc, char *argv[])
{
    device = CreateDevice(Vector2i(800, 600), "R3D Engine 2.0");
    char buf[128];
    int fps=0;
    double lastTime=device->getTime();

    TaskScheduler *ts = device->getTaskScheduler();

    MyTask mytask(ts);
    ts->scheduleTask(&mytask);

    while(device->isRunning()) {
        device->update();
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