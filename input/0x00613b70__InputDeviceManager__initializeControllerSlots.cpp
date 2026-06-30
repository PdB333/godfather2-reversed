// FUNC_NAME: InputDeviceManager::initializeControllerSlots

#include <cstdint>

// Global constants
const int32_t kInvalidDeviceId = 0xFFFFFFFF; // Value of DAT_00e2b1a4, likely -1

// Global 4x4 device ID matrix at 0x011f69b0 (16 int32s)
static int32_t g_controllerDeviceIDs[4][4];

// Global flags at 0x011f7430 – bit 0 indicates input system initialized
static uint32_t g_inputSystemInitFlags;

// Forward declaration: reinitializes the input subsystem (FUN_00614a50)
void InputDeviceManager::reinitializeInputSystem();

void InputDeviceManager::initializeControllerSlots()
{
    // Set each diagonal element to the invalid device ID; off-diagonals to zero.
    g_controllerDeviceIDs[0][0] = kInvalidDeviceId;
    g_controllerDeviceIDs[0][1] = 0;
    g_controllerDeviceIDs[0][2] = 0;
    g_controllerDeviceIDs[0][3] = 0;

    g_controllerDeviceIDs[1][0] = 0;
    g_controllerDeviceIDs[1][1] = kInvalidDeviceId;
    g_controllerDeviceIDs[1][2] = 0;
    g_controllerDeviceIDs[1][3] = 0;

    g_controllerDeviceIDs[2][0] = 0;
    g_controllerDeviceIDs[2][1] = 0;
    g_controllerDeviceIDs[2][2] = kInvalidDeviceId;
    g_controllerDeviceIDs[2][3] = 0;

    g_controllerDeviceIDs[3][0] = 0;
    g_controllerDeviceIDs[3][1] = 0;
    g_controllerDeviceIDs[3][2] = 0;
    g_controllerDeviceIDs[3][3] = kInvalidDeviceId;

    // If the input system was previously initialized, reinitialize it
    if ((g_inputSystemInitFlags & 1) != 0)
    {
        InputDeviceManager::reinitializeInputSystem();
    }
}