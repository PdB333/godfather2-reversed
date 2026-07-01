// FUNC_NAME: EARSAnimationComponent::updateAnimationState

#include <cstdint>

// Forward declarations of external engine functions
void stopAnimation(uint32_t animHandle); // FUN_00815060
void setAnimationSpeed(float speed);     // FUN_00846610
void startAnimation(float speed);        // FUN_008461f0

// EARSAnimationComponent – manages a single animation channel (blend tree node)
// Offsets:
// +0x34: Pointer to skeleton/blend root object (has vtable with method at offset 0x48)
// +0x38: Pointer to active animation state (or null if idle)
// +0x4c: Bitfield of flags (bit0: ?; bit5: ?; bit8: hasAnimation?)
// +0x5c: Handle of currently playing animation (or 0 if none)
// +0x60: Single byte flag (e.g., loop count, transition state)
class EARSAnimationComponent {
public:
    int32_t __thiscall updateAnimationState(bool forcePlay) {
        int32_t animState = *(int32_t*)(this + 0x38); // Pointer to active animation state
        uint32_t flags = *(uint32_t*)(this + 0x4c);
        
        // If no active animation state, clear the "has animation" flag and return failure.
        if (animState == 0) {
            if ((flags >> 5) & 1) {
                *(uint32_t*)(this + 0x4c) = flags & 0xffffffdf; // Clear bit5
            }
            return 0;
        }
        
        // Check if the component allows animation transition: 
        // if the "hasAnimation" flag (bit8) is not set and the animation state's "blocking" bit (bit3 at +0x150) is set, do nothing.
        if (!(flags & 0x100) && (*(uint32_t*)(animState + 0x150) >> 3 & 1)) {
            return 0;
        }
        
        // Current animation phase? (bits 11-14 of state flags at +0x118)
        uint32_t phase = (*(uint32_t*)(animState + 0x118) >> 0xb) & 0xf;
        
        if (phase == 0) {
            // Idle phase – check if we should start a new animation
            bool canPlay = !(flags & 1) && !(*(uint32_t*)(animState + 0x118) >> 1 & 1);
            if (canPlay && (forcePlay || (flags & 0x100))) {
                // Stop current animation and reset
                stopAnimation(*(uint32_t*)(this + 0x5c)); // FUN_00815060
                *(uint32_t*)(this + 0x5c) = 0;
                setAnimationSpeed(1.0f); // FUN_00846610: set blend speed to 1.0
                // Call virtual method on blend root to reset blend weight to 1.0
                (**(code**)(*(int32_t*)(*(int32_t*)(this + 0x34) + 4) + 0x48))(0, 0, 0, 1.0f);
            }
        } else if (phase == 2) {
            // Play phase – activate looping/start
            *(uint32_t*)(animState + 0x150) |= 1; // Set bit0 (playing flag)
            startAnimation(1.0f); // FUN_008461f0: start with speed 1.0
            *(int8_t*)(this + 0x60) = 0; // Reset loop counter / transition flag
            return 1;
        }
        return 0;
    }
};