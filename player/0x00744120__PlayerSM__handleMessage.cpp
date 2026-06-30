// FUNC_NAME: PlayerSM::handleMessage
// Function address: 0x00744120
// Player state machine message handler. Dispatches various actions based on message ID (offset from 10).
// This class contains pointers to subobjects at offsets +0x14 (Player object?), +0x15 (SubObject*), +0x17 (transform struct), +0x1b (another SubObject?).

class SubObject {
public:
    virtual int getTransform(int* playerObj, void* outTransform);          // vtable+0x1f8
    virtual int* doSomething(Vector3* inOut);                             // vtable+0x280
    virtual void setTarget(Vector3* src, Vector3* dst);                   // vtable+0x1c8
    virtual bool checkCondition(void* param);                             // vtable+0x1ec
    virtual bool isActive(void* player);                                  // vtable+0x1bc
};

class PlayerSM {
public:
    // +0x00: vtable
    int* vtable;                         // +0x00
    // +0x14 (offset 0x50): pointer to Player object
    int* m_player;                       // +0x50
    // +0x15 (offset 0x54): pointer into SubObject (base at ptr-0x48)
    int* m_subObjectMember;              // +0x54
    // +0x17 (offset 0x5C): transform struct? (used as output)
    Vector3 m_transform;                 // +0x5C
    // +0x1b (offset 0x6C): another pointer to subobject
    int* m_otherSubMember;               // +0x6C
    // ... other fields

    SubObject* getSubObject() {
        if (m_subObjectMember)
            return (SubObject*)(m_subObjectMember - 0x48);
        return nullptr;
    }

    SubObject* getOtherSubObject() {
        if (m_otherSubMember)
            return (SubObject*)(m_otherSubMember - 0x48);
        return nullptr;
    }

    int __thiscall handleMessage(int param2, int param3, int param4, int messageID, int param6);
};

// Forward declarations of some helper functions (likely from other modules)
extern int __stdcall createEffect(int a, int b, int c, float d, float e); // FUN_007347e0
extern Vector3* getPosition(int* playerObj, Vector3* outPos);             // FUN_00875af0
extern int __stdcall startSound(int a, int b);                            // FUN_006fbc40
extern void __stdcall triggerEvent(uint hash, int offset, int data, int unused); // FUN_007f96a0
extern void stopSound();                                                  // FUN_006fbc70
extern void FUN_00743da0();                                               // unknown
extern void FUN_007f41e0();                                               // unknown
extern void setGlobalFlag(int flag);                                      // FUN_004abc20
extern int FUN_00878ca0(int* player, Vector3* pos);                      // likely set position/rotation
extern void FUN_00742c10();                                               // unknown
extern int getFrameNumber();                                              // FUN_00471610
extern float vectorDistance(Vector3* a, Vector3* b);                      // FUN_0045c470
extern int FUN_0073b060(int* obj);                                        // unknown
extern void FUN_009b0820(int* obj, float val, int mode);                 // unknown
extern void FUN_007429b0();                                               // unknown
extern void FUN_007429f0();                                               // unknown
extern int __stdcall baseHandleMessage(int p2, int p3, int p4, int msg, int p6); // FUN_004ac700

int __thiscall PlayerSM::handleMessage(int param2, int param3, int param4, int messageID, int param6) {
    int retVal = 1;
    switch (messageID - 10) {
    case 0: // messageID == 10
        if (m_player != nullptr && m_subObjectMember != 0x48) {
            Vector3 local_18 = {0,0,0};
            SubObject* sub = getSubObject();
            if (sub != nullptr) {
                // Get transform data from subobject
                if (sub->getTransform(m_player, &local_18)) {
                    Vector3* pos = getPosition(m_player, &local_18);
                    // Call vtable+0x2c on this object (maybe set target position)
                    ((int(__stdcall*)(Vector3*, int, int, int, float, float)) (this->vtable[0x2c/4]))(pos, 0, 1, 1, 1.0f, 1.0f);
                    return 1;
                }
            }
        }
        break;
    case 1: // messageID == 11
        {
            int effect = createEffect(1, 0, 0, 1.0f, 1.0f);
            ((int(__stdcall*)(int)) (this->vtable[0x2c/4]))(effect);
            return 1;
        }
    default: // messageID == 12 goes to base handler
        return baseHandleMessage(param2, param3, param4, messageID, param6);
    case 3: // messageID == 13
        FUN_00743da0();
        return 1;
    case 4: // messageID == 14
        if (m_player != nullptr) {
            SubObject* sub = getSubObject();
            if (sub && sub->isActive(m_player)) {
                float threshold = *(float*)0x00d5ef70; // global threshold
                if (threshold < (float)m_transform.x) { // using m_transform as some float field
                    int soundHandle = startSound(0, 0);
                    triggerEvent(0x841360a0, 0x94, soundHandle, 0);
                    stopSound();
                    return 1;
                }
            }
        }
        break;
    case 5: // messageID == 15
        {
            Vector3 local_18 = {0,0,0};
            SubObject* sub = getSubObject();
            if (sub != nullptr) {
                sub->checkCondition(m_transform);
                if (sub->doSomething(&local_18) != 0) {
                    FUN_007f41e0();
                    setGlobalFlag(0x80000);
                    if (m_subObjectMember != 0) {
                        FUN_00878ca0(m_player, &m_transform);
                        return 1;
                    }
                    FUN_00878ca0(m_player, &m_transform);
                    return 1;
                }
            }
        }
        break;
    case 6: // messageID == 16
        FUN_00742c10();
        return 1;
    case 7: // messageID == 17
        if (m_otherSubMember != nullptr && m_otherSubMember != 0x48) {
            int frameA = getFrameNumber();
            int frameB = getFrameNumber();
            Vector3 posA = *(Vector3*)(frameA + 0x30);
            Vector3 posB = *(Vector3*)(frameB + 0x30);
            float dist = vectorDistance(&posA, &posB);
            float threshold = *(float*)0x00d5f53c;
            if (dist < threshold) {
                int otherBase = (int)getOtherSubObject();
                if (otherBase != 0) {
                    int subBase = (int)getSubObject();
                    FUN_009b0820(subBase, *(float*)0x00d5ef88, 1);
                    return 1;
                }
            }
        }
        break;
    case 8: // messageID == 18
        FUN_00878ca0(m_player, &m_transform);
        return 1;
    case 9: // messageID == 19
        {
            SubObject* sub = getSubObject();
            if (sub != nullptr) {
                sub->setTarget(&m_transform, &m_transform);
                return 1;
            }
            // Fallback: call with null? (likely decompiler artifact)
            return 1;
        }
    case 10: // messageID == 20
        FUN_007429b0();
        return 1;
    case 11: // messageID == 21
        FUN_007429f0();
        return 1;
    case 12: // messageID == 22
        break; // falls through to return 1
    }
    return retVal;
}