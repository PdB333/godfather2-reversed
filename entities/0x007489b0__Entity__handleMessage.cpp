// FUNC_NAME: Entity::handleMessage

#include <cstdint>

// Forward declarations of external functions
extern void FUN_00751e70();                     // unknown
extern void FUN_00751ec0();                     // unknown
extern void FUN_007f41e0();                     // unknown
extern void setFlag(uint32_t flags);            // FUN_004abc20
extern void clearFlag(uint32_t flags);          // FUN_004abdd0
extern bool FUN_0080e8e0(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t); // default handler
extern void FUN_009a8830(void*, void*, void*, float); // matrix/animation transformation

class Entity {
public:
    // +0x50: animation data pointer
    void* m_animationData;
    // +0x58: animation state (0 = none, 0x48 = special state)
    uint32_t m_animationState;
    // +0x60: animation matrix (12 bytes = 4x3?)
    uint8_t m_animationMatrix[12];
    // +0x78: default callback (function pointer)
    void (*m_defaultCallback)();
    // +0x8C: optional transform callback (may be null)
    void (*m_transformCallback)(void*);

    // vtable entry at offset 0x2c (method idx 11)
    // Signature: void (Entity::*)(void* trans, bool a, bool b, bool c, float d, float e)
    void applyTransform(void* trans, bool a, bool b, bool c, float d, float e);

    bool __thiscall handleMessage(uint32_t param2, uint32_t param3, uint32_t param4, uint32_t messageId, uint32_t param6) {
        bool result = true;
        switch (messageId) {
        case 0x12: // 18 - play animation or state change
            if (m_animationState != 0 && m_animationState != 0x48) {
                uint8_t tempMatrix[12];             // local_c
                FUN_009a8830(m_animationData, m_animationMatrix, tempMatrix, 1.0f);
                return true;
            }
            break;

        case 0x13: // 19 - apply transform from callback
        {
            void* transformObj;
            if (m_transformCallback != nullptr) {
                transformObj = m_transformCallback(this + 0x78); // pass address of m_defaultCallback?
            } else {
                transformObj = m_defaultCallback(); // returns void*?
            }
            // Call vtable method at offset 0x2c
            applyTransform(transformObj, true, true, false, 1.0f, 1.0f);
            return true;
        }

        case 0x14: // 20
            FUN_00751e70();
            return true;

        case 0x15: // 21
            FUN_00751ec0();
            return true;

        case 0x16: // 22 - set special flags
            FUN_007f41e0();
            setFlag(0x1000000);
            setFlag(0x20);
            return true;

        case 0x17: // 23 - clear flag
            clearFlag(0x20);
            return true;

        default:
            result = FUN_0080e8e0(param2, param3, param4, messageId, param6);
        }
        return result;
    }
};