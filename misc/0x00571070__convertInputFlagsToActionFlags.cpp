// FUNC_NAME: convertInputFlagsToActionFlags
uint __fastcall convertInputFlagsToActionFlags(void* inputState)
// Reads a uint at offset 0x10 from inputState, interprets bits as raw input flags,
// and converts to a different action flag set with early return on bit 12.
{
    uint rawFlags = *(uint*)((char*)inputState + 0x10); // +0x10: raw input bitfield (likely from controller or keyboard)
    uint actionFlags = 0;

    if ((rawFlags >> 5) & 1)          // bit5
        actionFlags |= 0x20;          // action flag: e.g., "move up"
    if ((rawFlags >> 6) & 1)          // bit6
        actionFlags |= 0x1;           // action flag: e.g., "move down"
    if ((rawFlags >> 0xB) & 1)        // bit11
        actionFlags |= 0x100;         // action flag: e.g., "action button"
    if ((rawFlags >> 0xC) & 1)        // bit12
        return actionFlags | 4;       // early return, bit12 overrides bit13
    if ((rawFlags >> 0xD) & 1)        // bit13
        actionFlags |= 8;             // action flag: e.g., "another action"

    return actionFlags;
}