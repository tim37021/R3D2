#ifndef _R3D_UTILS_TEXTURELOADER_H_
#define _R3D_UTILS_TEXTURELOADER_H_

#include <R3D/Core/ThreadTask.h>
#include <R3D/Rendering/Image.h>
#include <string>

namespace r3d
{
    namespace core
    {
        class TaskScheduler;
    }

    namespace rendering
    {
        class TextureManager;
        class Texture;
    }

    namespace utils
    {
        class AsyncTextureLoaderTask;
        class AsyncTextureLoaderUploadTask: public core::Task
        {
        public:
            friend class AsyncTextureLoaderTask;
            virtual void execute() override final;
        private:
            AsyncTextureLoaderTask *m_Parent;

            AsyncTextureLoaderUploadTask(AsyncTextureLoaderTask *parent_task);
        };

        class AsyncTextureLoaderTask: public core::ThreadTask
        {
            friend AsyncTextureLoaderUploadTask;
        public:
            AsyncTextureLoaderTask(core::TaskScheduler *ts, rendering::TextureManager *tmgr, 
                const std::string &resource, const std::string &filename);

            bool ready() const
            { return m_Texture == m_TextureDone; }

            rendering::Texture *getTexture() const
            { return m_Texture; }
        private:
            rendering::Image m_Image;
            rendering::Texture *m_Texture, *m_TextureDone;
            AsyncTextureLoaderUploadTask m_Uploader;
        };
    }
}

#endif