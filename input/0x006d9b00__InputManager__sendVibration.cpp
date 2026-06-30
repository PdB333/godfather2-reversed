// FUNC_NAME: InputManager::sendVibration
#include <cstdint>

// Vibration command structure used by the input command queue
// Offsets: +0x00 type, +0x04 dataSize, +0x08 flags
struct VibrationCommand {
    uint32_t type;      // Command type (2 = vibration)
    uint32_t dataSize;  // Size of the vibration data payload (0x10 = 16 bytes)
    uint32_t flags;     // Flags (0 = none)
};

// Forward declaration: returns a pointer to a function pointer stored in a global/singleton
typedef void (*CommandFunc)(uint32_t controllerIndex, VibrationCommand* cmd);
CommandFunc* getCommandQueue();  // Returns pointer to the command function pointer

void InputManager::sendVibration(uint32_t controllerIndex)
{
    // Retrieve the function pointer from the command queue singleton
    CommandFunc* funcPtr = getCommandQueue();  // e.g., InputManager::getCommandQueue()
    CommandFunc func = *funcPtr;               // First dereference: get the actual function

    // Build a vibration command (type = 2, size = 0x10, flags = 0)
    VibrationCommand cmd;
    cmd.type     = 2;     // kVibrationCommandType
    cmd.dataSize = 0x10;  // sizeof(VibrationData) – e.g., motor speed, duration, etc.
    cmd.flags    = 0;     // No special flags

    // Dispatch the command to the input system
    func(controllerIndex, &cmd);
}