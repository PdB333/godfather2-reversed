// FUNC_NAME: InputController::update
// Function at 0x0045f020
// Polls an input device (XInput controller) and processes its state.
// Returns modified previousResult (low byte cleared) if device not present,
// or result from device state processing.
// The function takes this (pointer to InputController), plus 3 additional parameters:
// param_2: likely an output buffer for initial input event
// param_3, param_4: likely output buffers for ongoing input (e.g., axis/button data)

int __thiscall InputController::update(
    int this_ptr,
    int param_2,
    int param_3,
    int param_4)
{
    int deviceState;  // was iVar3, from offset 0x218
    uint processedResult; // was uVar2
    uint result; // placeholder for clarity

    deviceState = *(int *)(this_ptr + 0x218); // m_pDevice (pointer to active device state)
    // Start with previousResult (value passed in EAX implicitly), keep high 24 bits
    processedResult = previousResult >> 8; // preserve upper bits

    if (deviceState != 0) {
        // Device is present, read its current state
        processedResult = FUN_00573440(); // readDeviceInput() - returns a uint with status/buttons
        int currentTick = DAT_01205224; // s_currentTick or global sequence number

        if ((char)processedResult != 0) {
            // Device state changed (low byte non-zero)
            if (*(int *)(this_ptr + 0x23c) != DAT_01205224) {
                // First time processing this state: handle initial input
                int ret = FUN_00571350(param_2); // handleInitialInput(param_2)
                *(int *)(this_ptr + 0x23c) = currentTick;
                return ret;
            }
            else {
                // Already processed this tick: handle ongoing input
                int ret = FUN_00571490(deviceState, param_3, param_4); // handleOngoingInput(deviceState, param_3, param_4)
                *(int *)(this_ptr + 0x23c) = currentTick;
                return ret;
            }
        }
        // Low byte zero: no change, shift processedResult down
        processedResult = processedResult >> 8;
    }
    // Device not present or no change: return modified previousResult (clear low byte)
    return processedResult << 8; // equivalent to previousResult & 0xFFFFFF00
}