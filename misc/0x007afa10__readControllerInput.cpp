// FUNC_NAME: readControllerInput
// Address: 0x007afa10
// Role: Polls input device state and processes a masked button event.

#include <cstdint>

// Global constants (from data sections)
extern uint32_t DAT_00d5ccf8; // Possibly device ID or handle
extern uint32_t DAT_00e44680; // Bitmask for specific button (e.g., A button)

// Underlying helper functions (not shown)
void getInputDeviceState(uint32_t deviceId, uint32_t* outUnused, uint32_t* outButtons,
                         uint32_t param4, uint32_t param5, uint32_t param6,
                         uint32_t param7, uint32_t param8);
void processButtonPress(uint32_t maskedState);

void readControllerInput(void)
{
    uint32_t buttonState = 0;      // Receives raw button flags
    uint32_t unusedOutput = 0;     // Not used after call

    // Call the engine's input polling function.
    // The repeated DAT_00d5ccf8 suggests a device handle or mode.
    getInputDeviceState(0, &unusedOutput, &buttonState,
                        0, 0,
                        DAT_00d5ccf8, DAT_00d5ccf8, DAT_00d5ccf8);

    // Extract the specific button (e.g., confirm/action) and dispatch it.
    processButtonPress(buttonState & DAT_00e44680);
}