#ifndef _R3D_CORE_INPUT_H_
#define _R3D_CORE_INPUT_H_

namespace r3d
{
    namespace core
    {
        enum class KeyCode
        {
            KEY_A=1,
            KEY_B,
            KEY_C,
            KEY_D,
            KEY_E,
            KEY_F,
            KEY_G,
            KEY_H,
            KEY_I,
            KEY_J,
            KEY_K,
            KEY_L,
            KEY_M,
            KEY_N,
            KEY_O,
            KEY_P,
            KEY_Q,
            KEY_R,
            KEY_S,
            KEY_T,
            KEY_U,
            KEY_V,
            KEY_W,
            KEY_X,
            KEY_Y,
            KEY_Z,

            KEY_LEFT,
            KEY_RIGHT,
            KEY_UP,
            KEY_DOWN,

            KEY_ENTER,

            KEY_LAST
        };

        class Input
        {
        public:
            virtual ~Input()=default;
            virtual void update()=0;
            virtual bool isKeyDown(KeyCode)=0;
            virtual bool isKeyUp(KeyCode)=0;
            virtual bool isKeyHold(KeyCode)=0;
        };
    }
}

#endif