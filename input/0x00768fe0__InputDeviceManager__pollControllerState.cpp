// FUNC_NAME: InputDeviceManager::pollControllerState
#include <cstdint>

// Offset +0x5c: likely controller index or device handle
void __fastcall InputDeviceManager::pollControllerState() {
    // Get timestamp from system (e.g., GetTickCount)
    uint32_t timestamp = getSystemTimestamp(); // FUN_0043b490

    // Send debug/log message with timestamp (message ID 0x40936, flag 0x80000000)
    sendDebugMessage(0x40936, 0x80000000, &timestamp, 1); // FUN_00540bc0

    // Initialize axis state buffer (three int32 values: e.g., left stick X/Y, triggers?)
    int32_t axisX = 0;
    int32_t axisY = 0;
    int32_t axisZ = 0;

    // 20-byte buffer for device name/serial
    char deviceName[20] = {0};

    // Retrieve controller state using member at +0x5c (controller handle/index)
    // Three global variables are likely calibration constants: min, max, default/deadzone
    getControllerAxisState(
        *(int32_t*)(this + 0x5c),  // +0x5c: controller ID or pointer
        &axisX,                     // output axis X
        g_controllerMin,           // _DAT_00d65bd4
        g_controllerMax,           // _DAT_00d65bd8
        g_controllerDefault,       // _DAT_00d65bdc
        deviceName                 // output device identifier (20 chars)
    ); // FUN_00720c90
}