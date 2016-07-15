#include <R3D/R3D.h>
#include <cstdio>

using namespace r3d;

using namespace core;
using namespace rendering;

Device *device=nullptr;


class TaskTextureLoadFinish: public Task
{
public:
    TaskTextureLoadFinish(TextureManager *tmgr, Image &img)
    : m_Img(img), m_Tmgr(tmgr)
    {
        
    }
    virtual void execute()
    {
        Texture *text = m_Tmgr->registerTexture("test.png");
        text->load(m_Img);
        printf("Async Texture loading completed width=%d height=%d\n", m_Img.getSize().x, m_Img.getSize().y);
    }
    Image &m_Img;
    TextureManager *m_Tmgr;
};

class TaskTextureLoad: public ThreadTask
{
public:
    TaskTextureLoad(TaskScheduler *ts, TextureManager *tmgr, const std::string &filename):
        ThreadTask(ts, [&](){
            std::this_thread::sleep_for(std::chrono::seconds(1));
            m_Image.loadFromFile(filename);
        }, 
        &m_Finish), m_Finish(tmgr, m_Image)
    {

    }
private:
    Image m_Image;
    TaskTextureLoadFinish m_Finish;
};

int main(int argc, char *argv[])
{
    device = CreateDevice(Vector2i(800, 600), "R3D Engine 2.0");
    char buf[128];
    int fps=0;
    double lastTime=device->getTime();

    TaskScheduler *ts = device->getTaskScheduler();

    TaskTextureLoad mytask(ts, device->getTextureManager(), "test.png");
    ts->scheduleTask(0, &mytask);

    while(device->isRunning()) {
        device->update();

        if(device->getInput()->isKeyDown(KeyCode::KEY_ENTER))
            device->stop();

        device->swapBuffers();

        fps++;
        if(device->getTime() - lastTime>1.0) {
            sprintf(buf, "R3D Engine 2.0 - %.1f fps", device->getFrameRate());
            device->setWindowCaption(buf);
            fps=0;
            lastTime = device->getTime();
        }
    }
    
    DestroyDevice(device);
    return 0;
}