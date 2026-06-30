// FUNC_NAME: ControllerState::getActionIndex
// Determines the action index based on button flags and state.
// param_1: pointer to controller state structure (this)
// Returns: action index (0-6) mapped from flags.
// Offsets: +0x08 = uint flags, +0x04 = byte buttonState, +0x28 = byte unknownByte
__fastcall uint ControllerState::getActionIndex(void* thisPtr)
{
    uint flags = *(uint*)((byte*)thisPtr + 0x08); // +0x08: input flags (bitfield)
    // Check specific flag combinations in priority order.
    if ((flags & 0x20) != 0) {
        return 6;
    }
    if ((flags & 0x0C) != 0) { // bits 2 or 3
        return 3;
    }
    if (*(char*)((byte*)thisPtr + 0x28) != 0) { // +0x28: some byte indicating action
        return 2;
    }
    // Default path: if buttonState is not 1 and flag 0x10 is clear
    if (*(char*)((byte*)thisPtr + 0x04) != 1 && (flags & 0x10) == 0) {
        if ((flags & 0x8000) != 0) {
            return 5;
        }
        return (flags >> 0x0E) & 4; // bit 14 yields 4 or 0
    }
    return 1;
}