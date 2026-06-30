// FUNC_NAME: PlayerAnimationSM::updateBlendTransition

#include <cstdint>

class PlayerAnimationSM {
public:
    // +0x00: vtable pointer (from PlayerAnimationSM)
    // +0x50: pointer to owning entity (PlayerCharacter or similar) - large class with fields at 0x1D60, 0x1D64, etc.
    // +0x58: blend timer (float) - elapsed time since last state change

    void updateBlendTransition() {
        // Get pointer to the owning entity (derived from PlayerCharacter or NPC)
        int* entityPtr = *(int**)(this + 0x50); // entity's base (first field is vtable)
        // Get simulation time manager? Returns a pointer with a float at +0x34 (delta time?)
        int* timeManager = getSimTimeManager();
        float blendTimer = *(float*)(this + 0x58) - *(float*)(timeManager + 0x34); // subtract maybe deltaTime

        // Determine if we are in a transition block (player controlled or scripted)
        int transitionBlock;
        if (**(int**)(DAT_012233a0 + 4) == 0) {
            transitionBlock = 0;
        } else {
            transitionBlock = **(int**)(DAT_012233a0 + 4) - 0x1f30; // some offset
        }

        // entity fields at offsets 0x1D60 and 0x1D64 (int arrays used as floats)
        float blendTimeThreshold = (float)entityPtr[0x759]; // +0x1D64
        float blendScale = (float)entityPtr[0x758];       // +0x1D60

        if (blendTimer <= blendTimeThreshold) {
            // Still within blend window, start new blend ?
            startAnimationBlend((blendTimer + _DAT_00d5780c) * blendScale, 1, transitionBlock);
            // Call virtual function at vtable index 0x234/4 = 141 (e.g., setBlendState)
            (**(void (__thiscall**)(int))(**(int**)(this + 0x50) + 0x234))();
        } else {
            // Blend time expired, stop previous blend
            (**(void (__thiscall**)(int))(*(int*)(*(int**)(this + 0x50)) + 0x288))(1); // stopBlend
            (**(void (__thiscall**)(int,int))(**(int**)(this + 0x50) + 0x234))(2,1);  // setBlendState with args
            // Set flags to indicate blend complete or forced
            uint32_t* flags = (uint32_t*)(*(int*)(this + 0x50) + 0x1b94);
            *flags |= 0x10000000; // bit 28

            // Check if animation has finished (virtual at +0xc0 = getPlaybackTime)
            float playlistTime = (**(float (__thiscall**)(int))(*(int*)(*(int**)(this + 0x50)) + 0xc0))();
            if (playlistTime <= 0.0f) {
                // Animation ended naturally
                *flags |= 0x40; // bit 6
            }
        }

        // Additional check: if animation already ended, trigger a transition or cleanup
        float playbackTime = (**(float (__thiscall**)(int))(*(int*)(*(int**)(this + 0x50)) + 0xc0))();
        if (playbackTime <= 0.0f) {
            getSimTimeManager();
            (**(void (__thiscall**)(int))(**(int**)(this + 0x50) + 0x28c))(); // call endBlend or finish
            debugPrint(&stack0xffffffd0, DAT_0112afd8, 0); // likely debug log
            return;
        }

        // Check blend ratio (time / duration) against threshold and state flag
        float currentTime = (**(float (__thiscall**)(int))(*(int*)(*(int**)(this + 0x50)) + 0xc0))();
        float duration = (**(float (__thiscall**)(int))(*(int*)(*(int**)(this + 0x50)) + 0xc4))();
        if ((currentTime / duration) <= _DAT_00d699ec && 
            ((*(uint8_t*)(*(int*)(this + 0x50) + 0x1b96) & 1) == 0)) {
            // Time to force transition or end blend
            getSimTimeManager();
            (**(void (__thiscall**)(int))(**(int**)(this + 0x50) + 0x28c))(); // finishBlend
            debugPrint(&stack0xffffffd0, DAT_0112afd8, 0);
            uint32_t* flags = (uint32_t*)(*(int*)(this + 0x50) + 0x1b94);
            *flags |= 0x10000; // bit 16
        }
    }

private:
    // Placeholder for unknown functions; actual names from game context
    int* getSimTimeManager(); // FUN_00471610 - returns pointer with delta time at +0x34
    void startAnimationBlend(float, int, int); // FUN_00801520
    void debugPrint(void*, int, int); // FUN_00408a00 - likely logging

    // Global constants from game data
    static constexpr float _DAT_00d5780c = 0.0f; // from actual binary
    static constexpr float _DAT_00d699ec = 0.5f; // blend threshold (example)
    static constexpr int DAT_012233a0 = 0x12233a0; // some global
    static constexpr int DAT_0112afd8 = 0x112afd8; // debug string
};