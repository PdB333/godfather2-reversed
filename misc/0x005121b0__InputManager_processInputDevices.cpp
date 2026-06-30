// FUNC_NAME: InputManager_processInputDevices

// Address: 0x005121b0
// Role: Polls input devices and dispatches input events.
// Retrieves up-to-date device states, and if a specific flag is set,
// triggers a device initialization or reset callback.
// Then it passes each state buffer to a core input processing function
// for further handling (e.g., mapping to game actions).

#include <cstdint>

// External globals (from input manager singleton or device manager)
extern void* gInputManager;        // DAT_0121b0ac
extern void* gInputProcessingCtx;  // DAT_0121a394, likely the main input handler

// Forward declarations of called subroutines (assumed names)
void getDeviceStates(uint8_t state16[16], uint8_t state28[28]);   // FUN_00535640
void handleDeviceReset();                                         // FUN_006063b0
void processDeviceInput(void* ctx, uint32_t deviceIndex, uint8_t state[16]); // FUN_0060add0

void InputManager_processInputDevices()
{
    uint8_t stateBufferA[16]; // 16-byte device state (e.g., XINPUT_STATE for controller 0)
    uint8_t stateBufferB[28]; // 28-byte device state (e.g., extended state for controller 1 or keyboard)

    // Retrieve current states from hardware layer
    getDeviceStates(stateBufferA, stateBufferB);

    // If a reinitialization flag is set (+0x0C in the manager), perform a device reset callback
    if (*(int32_t*)((uintptr_t)gInputManager + 0x0C) != 0)
    {
        handleDeviceReset();
    }

    // Process first device state (likely controller 0 or keyboard) using its index at +0x14
    processDeviceInput(gInputProcessingCtx,
                       *(uint32_t*)((uintptr_t)gInputManager + 0x14),
                       stateBufferA);

    // Process second device state (likely controller 1 or mouse) using its index at +0x10
    processDeviceInput(gInputProcessingCtx,
                       *(uint32_t*)((uintptr_t)gInputManager + 0x10),
                       stateBufferB);
}