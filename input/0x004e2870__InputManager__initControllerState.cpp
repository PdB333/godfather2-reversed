// FUNC_NAME: InputManager::initControllerState

#include <cstdint>

// Global variables (defined elsewhere)
extern int32_t g_numConnectedControllers;           // DAT_01218d30 - number of connected controllers
extern uint8_t g_controllerConfigs[];               // DAT_01218970 - array of controller configs (0xC0 bytes each)
extern uint8_t g_controllerInputState[];            // DAT_01218e54 - input state buffer (0xA0 bytes)

// Forward declarations of helper functions
void __fastcall InputManager_initBase(InputManager* this_);   // FUN_004e3d40
void __fastcall InputManager_initDefault(void);               // FUN_004e1c40 (no this pointer)
void __fastcall InputManager_initFromConfig(InputManager* this_, void* config); // FUN_004e22a0

class InputManager {
public:
    void initControllerState();
};

void InputManager::initControllerState() {
    // Call base initialization for this manager instance
    InputManager_initBase(this);

    if (g_numConnectedControllers == 0) {
        // No controllers connected: initialize with default settings
        InputManager_initDefault();
    } else {
        // One or more controllers connected: load configuration from the global table
        // Use g_numConnectedControllers as an index into the config array (each entry 0xC0 bytes)
        uint8_t* config = &g_controllerConfigs[g_numConnectedControllers * 0xC0];
        InputManager_initFromConfig(this, config);
    }

    // Clear 20 8-byte entries (0xA0 bytes total) in the controller input state buffer
    // Each iteration zeros a 4-byte (uint32_t) field at offset 0,8,16,... (up to 0x98)
    for (uint32_t offset = 0; offset < 0xA0; offset += 8) {
        *(uint32_t*)(g_controllerInputState + offset) = 0;
    }
}