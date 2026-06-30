// FUNC_NAME: Player::canPerformAction
#include <cstdint>

// Constants used for action threshold comparison
static const float kActionThresholdNormal = _DAT_00d62b64; // global float, normal threshold
static const float kActionThresholdSpecial = DAT_00d62b5c; // global float, alternative threshold

// External functions (renamed)
float* getGameTime();            // FUN_00471610 - returns pointer to current game time
void updateTimeDelta(void*);     // FUN_006bff90 - processes time delta
void triggerAction();            // FUN_0072eb30 - performs the actual action

// Returns 1 if the action should be performed, 0 otherwise
int __fastcall Player::canPerformAction(uintptr_t this) {
    int gameTimePtr = reinterpret_cast<int>(getGameTime());
    updateTimeDelta(reinterpret_cast<void*>(gameTimePtr + 0x30));

    uint32_t flags = *(uint32_t*)(this + 0x1f58);   // offset +0x1f58: flags bitfield
    uint32_t inputFlags = *(uint32_t*)(this + 0x1f54); // offset +0x1f54: input state flags

    float threshold;
    if (flags & (1 << 30)) {  // check bit 30: special mode active (e.g., vehicle)
        threshold = kActionThresholdSpecial;
    } else {
        threshold = kActionThresholdNormal;
    }

    // Check if game time delta (in x87 stack) is greater than threshold
    // and that input bit 10 (masked) is NOT set
    if ( (threshold < (float)extraout_ST0) &&
         ((~(static_cast<uint8_t>(inputFlags >> 10)) & 1) != 0) ) {
        triggerAction();
        return 1;
    }
    return 0;
}