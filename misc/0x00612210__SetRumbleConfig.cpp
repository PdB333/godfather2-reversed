// FUNC_NAME: SetRumbleConfig
// Address: 0x00612210
// Copies 16 dwords (64 bytes) of rumble/vibration parameters from source to global buffer,
// then if the force feedback manager exists, forwards the data to it.

#include <cstdint>

// Global buffer for rumble configuration data (64 bytes, 16 dwords)
// Located at 0x011f6970
static uint32_t gRumbleData[16]; // 0x011f6970

// Force feedback manager pointer (global at 0x012058e8)
// Expected to point to an object with methods:
// +0x10: pointer to device or context
// +0x50: device handle or flag
extern uint8_t* gForceFeedbackManager; // 0x012058e8

// Forward declaration of the function that applies rumble data
// This function is at 0x0060b020
void ApplyRumbleData(void* device, int32_t handle, const uint32_t* data);

void SetRumbleConfig(const uint32_t* source)
{
    // Copy 16 dwords from source to global buffer
    for (int i = 0; i < 16; i++)
    {
        gRumbleData[i] = source[i];
    }

    // If force feedback manager exists and has a valid device handle
    if (gForceFeedbackManager != nullptr)
    {
        int32_t* handlePtr = reinterpret_cast<int32_t*>(gForceFeedbackManager + 0x50);
        if (*handlePtr != 0)
        {
            void* device = *reinterpret_cast<void**>(gForceFeedbackManager + 0x10);
            ApplyRumbleData(device, *handlePtr, gRumbleData);
        }
    }
}