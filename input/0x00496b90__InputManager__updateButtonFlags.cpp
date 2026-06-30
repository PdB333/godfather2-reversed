// FUNC_NAME: InputManager::updateButtonFlags

// Function at 0x00496b90: Updates a bitfield in a controller state structure based on a virtual function call and a function table lookup.
// Called for each button/axis to set/clear the corresponding bit in the controller's active button mask.
// param_1 (unused): likely this of some base class, but not used directly; vtable is accessed via unaff_ESI (implicit this).
// param_2: pointer to ControllerState structure (+0x10 is a ushort bitmask)
// unaff_ESI: this pointer (InputManager object, with vtable at +4)
// unaff_DI: button index (0-31)

void InputManager::updateButtonFlags(void* param_1, ControllerState* state) {
    char keyState;       // raw key state returned by vcall
    char result;         // processed state from function table
    ushort bitMask;      // bit to update in the flag field
    InputManager* thisPtr; // implicit this (from ESI)
    byte buttonIndex;    // button/axis index (from DI)

    // Note: The actual code uses registers ESI (this) and DI (buttonIndex) directly.
    // Reconstruction assumes the member function receives these as implicit parameters.

    // Call virtual method at vtable index 3 (e.g., getRawButtonState) to get raw input state
    // The vtable pointer is obtained from *(int**)(thisPtr + 4)
    keyState = (*(code **)(*(int **)((int)thisPtr + 4) + 0xc))(); // +0xc = vtable[3]

    // If the index (keyState - 1) is within the function table range, call the mapping function
    if ((int)(uint)(byte)(keyState - 1) < g_keyFunctionCount) {
        // Call function from table to determine if the button is considered "pressed"
        result = g_keyFunctionTable[ (byte)(keyState - 1) ]();
    } else {
        result = '\0'; // no mapping → not pressed
    }

    // Build the bitmask for the current button index
    bitMask = (ushort)(1 << (buttonIndex & 0x1f)); // only bottom 5 bits matter for 16-bit mask

    if (result != '\0') {
        // Button is active: set the bit
        state->activeButtons = state->activeButtons | bitMask;
    } else {
        // Button is inactive: clear the bit
        state->activeButtons = state->activeButtons & ~bitMask;
    }
}