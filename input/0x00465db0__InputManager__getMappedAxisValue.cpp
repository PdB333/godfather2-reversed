// FUNC_NAME: InputManager::getMappedAxisValue
// Address: 0x00465db0
// Role: Retrieves a scaled analog axis value from a controller by mapping a game action ID to a controller axis index.

#include <cstdint>

// Global data (defined elsewhere in the binary)
extern uint8_t* g_pControllerDataArray;     // DAT_012233b4 - pointer to array of 0x44-byte controller structures
extern uint16_t g_actionIdTable[16];        // DAT_00e2e3d8 - mapping from slot index to action ID (2 bytes each)
extern uint32_t g_axisIndexTable[16];       // UNK_00e2e458 - mapping from slot index to axis offset within controller (0-15)
extern float g_sensitivityScale;             // DAT_00e44640 - global scaling factor

// Helper function (declared elsewhere)
bool isControllerConnected(uint32_t controllerIndex); // FUN_0040fa60

// Controller structure offsets (0x44 bytes each)
struct ControllerState {
    uint8_t  unk_0x00[0x42];               // +0x00 - unknown fields
    uint8_t  analogAxes[16];               // +0x42 - 16 byte-sized analog values (0-255)
    uint8_t  unk_0x52[0x18];               // +0x52 to +0x69
    uint8_t  isConnected;                  // +0x6a - non-zero if slot is active/connected
    uint8_t  unk_0x6b[0x44 - 0x6b];       // remaining
};

float InputManager::getMappedAxisValue(uint32_t controllerIndex, int32_t actionId) {
    if (!isControllerConnected(controllerIndex))
        return 0.0f;

    for (int slot = 0; slot < 16; ++slot) {
        if (g_actionIdTable[slot] == actionId) {
            uint8_t analogValue = 0;

            // Validate controller index and slot
            if ((controllerIndex & 0xFF) < 16) {
                ControllerState* ctrl = reinterpret_cast<ControllerState*>(g_pControllerDataArray + (controllerIndex & 0xFF) * 0x44);
                if (ctrl->isConnected && g_axisIndexTable[slot] < 16) {
                    analogValue = ctrl->analogAxes[g_axisIndexTable[slot]];
                }
            }

            // Scale the byte value (0-255) by the global sensitivity and return
            return static_cast<float>(analogValue) * g_sensitivityScale;
        }
    }

    return 0.0f;
}