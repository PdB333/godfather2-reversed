// FUNC_NAME: ActionController::canExecuteAction
// Address: 0x007ba5a0
// Reconstructed from Ghidra decompilation of The Godfather 2 (EARS engine, x86)
// Checks whether the current action can be executed given the system state and input locks

int __thiscall ActionController::canExecuteAction(ActionController* this) {
    // Read pointer at +0x58 (likely to some state/input device struct)
    // Then read dword at +0x1010 within that struct (maybe current action ID or key state)
    int actionId = *(int*)(*(int*)((char*)this + 0x58) + 0x1010);

    // If actionId matches one of the 'S', 'U', 'W', 'Y' key codes, action is blocked
    if (actionId == 0x53 || actionId == 0x55 || actionId == 0x57 || actionId == 0x59) {
        return 0; // Not allowed
    }

    // Check global flag via FUN_007b9ee0 (maybe system cutscene/menu lock)
    if (FUN_007b9ee0() != 0) {
        return 1; // Allowed: system not blocked?
    }

    // Read a byte at +0x74 (likely current command/gesture type or modifier)
    char commandByte = *(char*)((char*)this + 0x74);

    // Check commandByte against a long list of ASCII codes (mostly symbols and numbers)
    // Also check if actionId equals 'T', 'V', 'X', 'Z'
    if (
        (commandByte == -1) ||
        (commandByte == 0x01) ||
        (commandByte == 0x03) ||
        (commandByte == 0x07) ||
        (commandByte == 0x0b) ||
        (commandByte == 0x09) ||
        (commandByte == 0x05) ||
        (commandByte == 0x0d) ||
        (commandByte == 0x0f) ||
        (commandByte == 0x11) ||
        (commandByte == 0x25) ||  // '%'
        (commandByte == 0x13) ||
        (commandByte == 0x15) ||
        (commandByte == 0x19) ||
        (commandByte == 0x1d) ||
        (commandByte == 0x1b) ||
        (commandByte == 0x17) ||
        (commandByte == 0x1f) ||
        (commandByte == 0x21) ||  // '!'
        (commandByte == 0x23) ||  // '#'
        (commandByte == 0x27) ||  // '\''
        (commandByte == 0x29) ||  // ')'
        (commandByte == 0x2b) ||  // '+'
        (commandByte == 0x2d) ||  // '-'
        (commandByte == 0x2f) ||  // '/'
        (commandByte == 0x31) ||  // '1'
        (commandByte == 0x33) ||  // '3'
        (commandByte == 0x35) ||  // '5'
        (commandByte == 0x37) ||  // '7'
        (commandByte == 0x39) ||  // '9'
        (commandByte == 0x3b) ||  // ';'
        (actionId == 0x54) ||    // 'T'
        (actionId == 0x56) ||    // 'V'
        (actionId == 0x58) ||    // 'X'
        (actionId == 0x5a)       // 'Z'
    ) {
        // Call FUN_007f7e90 with -1 (maybe check if a certain interrupt is disabled)
        if (FUN_007f7e90(0xffffffff) == 0) {
            return 1; // Allowed
        }
    }

    return 0; // Not allowed
}