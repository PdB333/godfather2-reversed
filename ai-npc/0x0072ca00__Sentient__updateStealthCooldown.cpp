// FUNC_NAME: Sentient::updateStealthCooldown
// Function address: 0x0072ca00
// Role: Checks a cooldown condition (possibly stealth/detection) and sets a dirty flag if threshold exceeded.
// Uses a global frame counter to avoid repeated checks within same frame.

#include <cstdint>

// External globals (addresses from game binary)
extern int DAT_01205224;          // Current frame number / time tick
extern float _DAT_00d62b24;      // Stealth or detection threshold

// External helper: returns a float value from an unknown input
extern float __stdcall FUN_004702b0(uint32_t input);

class Sentient {
public:
    // Offset +0x1F58: Flag bits (bit 7 = stealthDirty)
    uint32_t flags;
    // Offset +0x2058: Frame when stealth was last dirtied
    int lastStealthFrame;

    void updateStealthCooldown(uint32_t someInput) {
        int currentFrame = DAT_01205224;
        // Only proceed if stealth flag is not already set OR the last dirtied frame differs
        if (((flags >> 7) & 1) == 0 || lastStealthFrame != currentFrame) {
            float value = FUN_004702b0(someInput);
            if (value < _DAT_00d62b24) {
                lastStealthFrame = currentFrame;
                flags |= 0x80; // Set stealth dirty flag (bit 7)
            }
        }
    }
};