// FUNC_NAME: Sentient::handleMessage

// Function at 0x0073dcd0: Handles various messages (event IDs 0x12, 0x13, 0x14) for a Sentient or Character entity.
// param_5 is the message ID (e.g. kMsgAnimStart=0x12, kMsgSoundPlay=0x13, kMsgAction=0x14)
// If unhandled, delegates to base class handler at 0x0080e8e0.

#include <cstdint>

// Forward declarations for called functions (placeholder names)
extern uint32_t FUN_0080e8e0(uint32_t, uint32_t, uint32_t, int32_t, uint32_t);
extern uint32_t FUN_007822d0(uint32_t);
extern void FUN_0044b210(uint32_t);
extern void FUN_004daf90(uint32_t*);
extern int32_t FUN_0043b870(uint32_t); // e.g. audio manager check
extern uint32_t FUN_006fbc40(int32_t, int32_t); // e.g. getSoundBank
extern void FUN_006f3eb0(uint32_t, int32_t, uint32_t, uint32_t); // e.g. playSound
extern void FUN_006fbc70(); // e.g. releaseSoundBank

// Global audio manager pointer (likely AudioDataManager*)
extern uint32_t DAT_0112a9fc;

// Constants for message IDs
const int32_t kMsgAnimStart = 0x12;   // 18
const int32_t kMsgSoundPlay = 0x13;   // 19
const int32_t kMsgAction    = 0x14;   // 20

// Class members accessed via this pointer offsets (relative to this):
// +0x58: m_pSomeComponent (pointer, used for animations)
// +0x5C: m_pPendingAction (pointer, reset on action)
// +0x64: m_pOwnerOrComponent (value that is either 0, 0x48, or a pointer to a subobject)
// +0x6C: m_animValue (float or int used with animation)

class Sentient {
public:
    // Virtual table likely includes this function at some slot.
    uint32_t __thiscall handleMessage(uint32_t param_2, uint32_t param_3, uint32_t param_4,
                                      int32_t msgId, uint32_t param_6);
};

uint32_t __thiscall Sentient::handleMessage(uint32_t param_2, uint32_t param_3,
                                            uint32_t param_4, int32_t msgId,
                                            uint32_t param_6) {
    int32_t* thisPtr = reinterpret_cast<int32_t*>(this);
    int32_t ownerOffset = thisPtr[0x19]; // offset 0x64: stores either 0, 0x48, or a pointer to a sub-struct

    if (msgId == kMsgAnimStart) {
        // Anim start message
        if ((ownerOffset != 0) && (ownerOffset != 0x48)) {
            // Compute base of parent object (assuming ownerOffset points to a member at offset 0x48 within parent)
            int32_t parentBase = (ownerOffset == 0) ? 0 : (ownerOffset - 0x48);
            // Call virtual function at vtable+0x2c on the object at parentBase+0x88
            // Arguments: (1, 0, 0, this->m_animValue (at +0x6C), 1.0f)
            (**(code**)(*reinterpret_cast<int32_t*>(parentBase + 0x88) + 0x2c))(
                1, 0, 0, thisPtr[0x1b], 0x3f800000 /* 1.0f */);
        }
    } else if (msgId == kMsgSoundPlay) {
        // Sound play message
        if ((ownerOffset != 0) && (ownerOffset != 0x48)) {
            int32_t parentBase = (ownerOffset == 0) ? 0 : (ownerOffset - 0x48);
            int32_t soundHandle = *reinterpret_cast<int32_t*>(parentBase + 0x8c); // offset 0xD4 (parentBase+0x8c) is sound handle
            if ((soundHandle != 0) && (thisPtr[0x16] != 0)) { // also check m_pSomeComponent
                int32_t audioCheck = FUN_0043b870(DAT_0112a9fc);
                if (audioCheck != 0) {
                    int32_t soundParentBase = (ownerOffset == 0) ? 0 : (ownerOffset - 0x48);
                    uint32_t sndHandle = *reinterpret_cast<uint32_t*>(soundParentBase + 0x8c);
                    uint32_t soundBank = FUN_006fbc40(0, 0);
                    FUN_006f3eb0(sndHandle, 1, soundBank, 0);
                    FUN_006fbc70();
                    return 1;
                }
            }
        }
    } else if (msgId == kMsgAction) {
        // Perform action
        int32_t someComponent = thisPtr[0x16]; // m_pSomeComponent
        if ((someComponent != 0) && (ownerOffset != 0) && (ownerOffset != 0x48)) {
            if (ownerOffset != 0) {
                uint32_t animEntry = FUN_007822d0(someComponent);
                FUN_0044b210(animEntry);
                return 1;
            }
            // else (fallback case, same code? Actually duplicate, probably due to decompiler)
            uint32_t animEntry = FUN_007822d0(someComponent);
            FUN_0044b210(animEntry);
            return 1;
        }
        // If no component, clear pending action if exists
        if (thisPtr[0x17] != 0) { // m_pPendingAction
            FUN_004daf90(reinterpret_cast<uint32_t*>(thisPtr + 0x17));
            thisPtr[0x17] = 0;
            return 1;
        }
    } else {
        // Unknown message: delegate to base class
        return FUN_0080e8e0(param_2, param_3, param_4, msgId, param_6);
    }
    return 1;
}