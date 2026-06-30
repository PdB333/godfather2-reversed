// FUNC_NAME: Sentient::attemptTargetAction
#include <cstdint>

// External function declarations (assumed from context)
extern "C" void* __fastcall FUN_008c74d0(void* ptr);
extern "C" void __fastcall FUN_006b4e30(int param1, int param2);

// Reconstructed function at 0x006b5a30
// Checks if the sentient can perform a target-oriented action based on animation state,
// flags, and target status. If conditions are met, triggers the action and returns 1.
uint32_t __fastcall Sentient::attemptTargetAction(Sentient* this_) {
    // +0x16c: current animation state index (likely an enum)
    int32_t animState = *(int32_t*)((uint8_t*)this_ + 0x16c);

    // +0x34: bitmask of state flags (e.g., busy, stunned, etc.)
    uint32_t stateFlags = *(uint32_t*)((uint8_t*)this_ + 0x34);

    // Check: bit 0 (1), and bits 0x120000 (e.g., covers certain action disallowing states)
    if ((stateFlags & 0x120000) == 0 &&
        (stateFlags & 1) == 0 &&
        // +0x40: pointer to a target entity (could be an enemy, object, etc.)
        *(void**)((uint8_t*)this_ + 0x40) != nullptr) {
        
        // Cast or resolve the target (FUN_008c74d0 likely returns a specific object pointer)
        void* target = FUN_008c74d0(*(void**)((uint8_t*)this_ + 0x40));
        if (target != nullptr) {
            // +0x84: flags on target object; check bit 5 (0x20) is clear
            // (~(byte)(flags >> 5) & 1) means the bit is not set
            if ( (~(uint8_t)(*(uint32_t*)((uint8_t*)target + 0x84) >> 5) & 1) != 0 ) {
                // Valid animation states are 2, 3, or 4 (e.g., idle, walking, running)
                if (animState == 2 || animState == 3 || animState == 4) {
                    FUN_006b4e30(0, 0); // initiate action (e.g., play animation, start combat move)
                    return 1;
                }
            }
        }
    }
    return 0;
}