// FUNC_NAME: ForceFeedbackManager::computeEffectMagnitude

// Address: 0x00496cf0
// This function calculates the rumble/force feedback magnitude for a given controller input.
// It interprets a 32-bit input word from a virtual function call (likely from a device interface)
// to determine motor type (low/high frequency) and scale factors.

// Globals (guessed names):
//   g_rumbleSystemInitialized - 0x01223998 (bit0 = already initialized)
//   g_masterRumbleScale - 0x01223994  (float)
//   g_rumbleSwapMultiplier - 0x00e2eff4 (float)
//   g_numRumbleProfiles - 0x01205464 (int, count of profile entries)
//   g_rumbleProfileTable - 0x01163ee8 (array of function pointers, each returning float)

// Offsets from 'this' (stored in ESI):
//   +0x04: Pointer to vtable (used to call a device method at vtable+0x20)
//   +0x118: float - multiplier A (context-specific, e.g. event intensity)
//   +0x11c: float - multiplier B (context-specific, e.g. distance/volume)

void __fastcall ForceFeedbackManager::computeEffectMagnitude(void* thisPtr, int deviceHandle, char swapChannels, int unused, float* outMagnitude)
{
    uint rawValue;
    uint motorType;
    uint motorIndex;
    uint scaleBits;
    char swapped;
    float baseScale;
    int profileIndex;
    float finalValue;

    // Call virtual function on the device interface at this+4 (vtable offset 0x20)
    // This function likely returns a 32-bit word encoding motor info and strength.
    rawValue = (*(code**)(*(int*)((int)thisPtr + 4) + 0x20))(deviceHandle);

    // Extract high byte components
    uint highByte = rawValue >> 8;
    uint motorBits = highByte & 0x3f;
    uint channelBits = highByte & 0xc0;

    if ((char)rawValue == 1) {
        // Motor type 1: Low-frequency (heavy rumble)
        swapped = 0;
        if (channelBits != 0) {
            if (channelBits == 0x40) {
                swapped = 1;               // Swap to high channel
            } else if (channelBits == 0x80) {
                swapped = swapChannels;    // Use caller-provided swap flag
            }
        }

        if (motorBits == 1) {
            // Use low-frequency motor index 0
            motorIndex = 0;
        } else if (motorBits == 2) {
            // Use low-frequency motor index 1
            motorIndex = 1;
        } else {
            return; // Unsupported motorBits, do nothing
        }

        // Initialize rumble system if not already done
        if ((g_rumbleSystemInitialized & 1) == 0) {
            g_rumbleSystemInitialized |= 1;
            g_masterRumbleScale = *(float*)0x00e2e210;  // some default scale constant
        }

        // Base scale from the upper 16 bits of rawValue
        float baseScale = (float)(rawValue >> 16) * g_masterRumbleScale;

        // Get a multiplier from another subsystem (e.g., game state, distance)
        profileIndex = FUN_00b93230(motorIndex);  // returns integer multiplier (e.g., 0 or 1)

        // Apply scaling factors from the object context
        finalValue = (float)profileIndex * *(float*)((int)thisPtr + 0x11c) * *(float*)((int)thisPtr + 0x118) * baseScale;

        if (swapped != 0) {
            // If swapped, multiply by a swap multiplier (e.g., cross-feed factor)
            finalValue *= g_rumbleSwapMultiplier;
        }

        *outMagnitude = finalValue;
    }
    else if ((char)rawValue == 2) {
        // Motor type 2: High-frequency (light rumble)
        int profileIndex = (int)(byte)(motorBits - 1);
        if (profileIndex < g_numRumbleProfiles) {
            // Call a profile function from the table; result is a long double (float10) cast to float
            float10 profileValue = (*(code**)(&g_rumbleProfileTable[profileIndex]))();
            *outMagnitude = (float)profileValue;
        } else {
            *outMagnitude = 0.0f;
        }
    }
    // Implicit return for other rawValue types? No, function ends.
}