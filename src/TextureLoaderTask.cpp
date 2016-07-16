#include <R3D/Utils/TextureLoaderTask.h>
#include <R3D/Rendering/TextureManager.h>
#include <R3D/Rendering/Texture.h>

namespace r3d
{
    namespace utils
    {
        AsyncTextureLoaderUploadTask::AsyncTextureLoaderUploadTask(AsyncTextureLoaderTask *parent)
            : m_Parent(parent)
        {

        }

        void AsyncTextureLoaderUploadTask::execute()
        {
            m_Parent->m_Texture = m_Parent->m_TextureDone;
            m_Parent->m_Texture->load(m_Parent->m_Image);
        }

        AsyncTextureLoaderTask::AsyncTextureLoaderTask(core::TaskScheduler *ts, rendering::TextureManager *tmgr, 
                const std::string &resource, const std::string &filename)
            : ThreadTask(ts, [&](){
                m_Image.loadFromFile(filename);
            }, &m_Uploader), m_Uploader(this)
        {
            m_Texture = tmgr->fetchTexture("DEFAULT_TEXTURE");
            m_TextureDone = tmgr->registerTexture(resource);
        }


    }
}