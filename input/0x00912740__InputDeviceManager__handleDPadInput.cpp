// FUNC_NAME: InputDeviceManager::handleDPadInput
// Address: 0x00912740
// Role: Handles D-pad button input (left/right/up/down) by registering a command and submitting a movement input structure.

#include <cstdint>

// Forward declarations of external functions and globals
void registerInputCommand(const char* commandName, int param2, void* commandMap, int param4);  // FUN_005a04a0
void submitMovementInput(void* inputStruct, int param2);  // FUN_00408a00

// Global variables
extern float gHorizontalInputValue;  // DAT_011304d8
extern float gVerticalInputValue;    // DAT_011301c0
extern void* gInputCommandMap;       // DAT_00d84448

// Represents a movement input: value (horizontal or vertical), plus padding
struct MovementInput {
    float value;     // +0x00
    int padding;     // +0x04
    char extra;      // +0x08
};

int InputDeviceManager::handleDPadInput(uint buttonIndex)
{
    MovementInput input;
    input.padding = 0;
    input.extra = 0;

    switch (buttonIndex) {
    case 6: // D-Pad Left
        registerInputCommand("MoveLeft", 0, gInputCommandMap, 0);
        input.value = gHorizontalInputValue;
        break;
    case 7: // D-Pad Right
        registerInputCommand("MoveRight", 0, gInputCommandMap, 0);
        input.value = gHorizontalInputValue;
        break;
    case 8: // D-Pad Up
        registerInputCommand("MoveUp", 0, gInputCommandMap, 0);
        input.value = gVerticalInputValue;
        break;
    case 9: // D-Pad Down
        registerInputCommand("MoveDown", 0, gInputCommandMap, 0);
        input.value = gVerticalInputValue;
        break;
    default:
        return 0; // Unhandled button, do nothing
    }

    submitMovementInput(&input, 0);
    return 0;
}