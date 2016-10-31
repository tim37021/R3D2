#include <R3D/R3D.h>

#include <litehtml.h>
#include <cstdio>
#include <cstdio>
#include <cmath>
using namespace r3d;

using namespace core;
using namespace rendering;

Device *device=nullptr;


RenderTarget *BuildGBuffer(Device *device, Vector2i size)
{
    RenderTarget *rt = device->addRenderTarget();
    TextureManager *tm = device->getTextureManager();
    std::vector<Texture *> textures = {tm->registerTexture("GBUFFER_COLOR")};
    for(auto texture: textures)
        texture->create(size, PixelFormat::PF_R8G8B8A8);
    rt->attachTextures(textures);
    Texture *depth_texture = tm->registerTexture("GBUFFER_DEPTH");
    depth_texture->create(size, PixelFormat::PF_D24);
    rt->attachDepthTexture(depth_texture);

    return rt;
}

int main(int argc, char *argv[])
{
    device = CreateDevice(Vector2i(800, 600), "R3D Engine 2.0");

    char buf[128];
    int fps=0;
    double lastTime=device->getTime();
    
    TextureManager *tm = device->getTextureManager();


    RenderTarget *rt = BuildGBuffer(device, {800, 600});

    while(device->isRunning()) {
        device->update();

        if(device->getInput()->isKeyDown(KeyCode::KEY_ESCAPE))
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