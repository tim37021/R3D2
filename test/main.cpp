#include <R3D/R3D.h>

#include <litehtml.h>
#include <cstdio>
#include <string>
#include <fstream>
#include <streambuf>
#include <cmath>

using namespace r3d;
using namespace core;
using namespace rendering;

Device *device=nullptr;


static std::string LoadFile(const char *filename)
{
    std::ifstream t(filename);
    return std::string(std::istreambuf_iterator<char>(t),
                     std::istreambuf_iterator<char>());
}

static RenderTarget *BuildGBuffer(Device *device, Vector2i size)
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

    ShaderProgram *program = device->addShaderProgram();
    program->create(LoadFile("vs2.txt").c_str(), LoadFile("fs2.txt").c_str());


    GLuint id;
    glGenVertexArrays(1, &id);

    auto *camera = device->getSceneManager()->getCamera();

    while(device->isRunning()) {
        device->update();

        if(device->getInput()->isKeyDown(KeyCode::KEY_ESCAPE))
            device->stop();

        if(device->getInput()->isKeyDown(KeyCode::KEY_L))
            tm->loadTextureFromFileAsync("./water.png", "water.png", nullptr);
        if(device->getInput()->isKeyDown(KeyCode::KEY_M))
            device->getSceneManager()->loadWavefrontAsync("sponza/sponza.obj");

        //auto view = LookAt({100.f, 100.f, 100.f}, {0.f}, {0.f, 1.f, 0.f});
        program->setUniform("vp", camera->getProjectionMatrix()*camera->getViewMatrix());
        program->setUniform("v", Matrix4(Matrix3(camera->getViewMatrix())));

        device->getDefaultRenderTarget()->bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        program->use();
        device->getSceneManager()->drawAll();
/*
        glBindVertexArray(id);
        program->use();
        tm->fetchTexture("./water.png")->bind(0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
*/
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