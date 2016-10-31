#include <R3D/R3D.h>

#include <litehtml.h>
#include <cstdio>
#include <cstdio>
#include <cmath>
using namespace r3d;

using namespace core;
using namespace rendering;

Device *device=nullptr;

int main(int argc, char *argv[])
{
    device = CreateDevice(Vector2i(800, 600), "R3D Engine 2.0");

    char buf[128];
    int fps=0;
    double lastTime=device->getTime();
    
    TextureManager *tm = device->getTextureManager();


    TaskStatus status;
    tm->loadTextureFromFileAsync("test.png", "test.png", &status);

    while(device->isRunning()) {
        device->update();

        tm->fetchTexture("test.png");

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