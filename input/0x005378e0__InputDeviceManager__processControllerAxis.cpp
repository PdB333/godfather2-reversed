// FUNC_NAME: InputDeviceManager::processControllerAxis

#include <cstdint>

struct ControllerState {
    uint16_t flags;  // +0
    uint16_t axisX;  // +2
    uint16_t axisY;  // +4
};

extern ControllerState g_controllerStateArray[0x1000];  // DAT_011a0f28
extern InputDeviceManager* g_inputDeviceManager;       // DAT_0121a394
extern uint8_t* g_inputDeviceManagerData;              // DAT_0121b0ac

extern void processAxisInput(InputDeviceManager* mgr, void* device, float axis[2]);  // FUN_0060ac80
extern void flushInputQueue();                                                        // FUN_006063b0

void InputDeviceManager::processControllerAxis(uint controllerIndex)
{
    // Ensure the index is valid (0x1000 = 4096, but real slots are 0-15)
    if (controllerIndex >= 0x1000) return;

    ControllerState* pState = &g_controllerStateArray[controllerIndex];

    // Convert raw 16-bit axis values to floats
    float rawAxisX = (float)pState->axisX;  // offset +2
    float rawAxisY = (float)pState->axisY;  // offset +4

    float axisPair[2] = { rawAxisX, rawAxisY };

    // Forward to the axis handler with device pointer from the manager
    void* devicePtr = *(void**)(g_inputDeviceManagerData + 0x20);
    processAxisInput(g_inputDeviceManager, devicePtr, axisPair);

    // If input queue is non-empty, flush it
    if (*(int32_t*)(g_inputDeviceManagerData + 8) != 0) {
        flushInputQueue();
    }
}