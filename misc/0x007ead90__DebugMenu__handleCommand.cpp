// FUNC_NAME: DebugMenu::handleCommand
int __thiscall DebugMenu::handleCommand(int *this, int arg1, int arg2, int arg3, int command, int arg4)
{
    int result;
    uint bitmask;
    char stateChar;
    float angle;
    float adjustedArg;
    float someValue;
    int *playerPtr; // this[0x16] -> pointer to player object

    playerPtr = (int *)this[0x16]; // offset 0x58 from this

    switch (command) {
    case 0x31: // '1' - clear flag
        bitmask = getToggleMask(); // FUN_006252f0
        *(uint *)(playerPtr + 0x1b94 / 4) &= ~bitmask; // clear bits at offset 0x1b94
        return 1;

    case 0x32: // '2' - set flag
        bitmask = getToggleMask();
        *(uint *)(playerPtr + 0x1b94 / 4) |= bitmask; // set bits at offset 0x1b94
        return 1;

    case 0x33: // '3' - set angle/time value
        // Virtual call at vtable offset 0x200 from player object
        someValue = (**(float (__thiscall **)(int *))(*(int *)playerPtr + 0x200))(playerPtr);
        adjustedArg = (float)arg1;
        if (arg1 < 0) {
            adjustedArg += 360.0f; // DAT_00e44578 (likely 360.0)
        }
        // DAT_00d5efb8 is a conversion factor (e.g., 0.1f or 1.0f)
        this[0x1e] = (int)(adjustedArg * 0.1f + someValue); // offset 0x78 from this
        updateSomething(); // FUN_007f9540
        return 1;

    case 0x34: // '4' - play sound based on state
        {
            int soundId = *(int *)(playerPtr + 0x2120 / 4); // offset 0x2120
            stateChar = *(char *)(playerPtr + 0x1b8c); // offset 0x1b8c
            if (stateChar == 0x03 || stateChar == 0x02) {
                // Virtual call at vtable offset 0x2c from this
                (**(void (__thiscall **)(int *, int, int, int, int, float))(*(int *)this + 0x2c))
                    (this, 0x2bc4b458, 1, 1, 0, soundId, 1.0f);
                return 1;
            }
            if (stateChar == 0x01) {
                (**(void (__thiscall **)(int *, int, int, int, int, float))(*(int *)this + 0x2c))
                    (this, 0xe3048536, 1, 1, 0, soundId, 1.0f);
                return 1;
            }
        }
        break;

    case 0x35: // '5' - start effect
        startEffect(0xb); // FUN_007f63e0
        return 1;

    case 0x36: // '6' - stop effect
        stopEffect(0xb); // FUN_007f6420
        return 1;

    default:
        result = defaultHandler(arg1, arg2, arg3, command, arg4); // FUN_007abec0
        return result;
    }

    return 1; // fallthrough for case 0x34 when no match
}