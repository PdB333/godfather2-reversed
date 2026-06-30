// FUN_004aee80: debugPrintCommand

// Function at 0x004aee80: Interprets a debug command message and prints its contents.
// The message structure at param_2 (msg) has:
//   +0: unknown (maybe size or padding, not used in this function)
//   +4: command type (4 bytes, integer)
//   +8: data payload (varies by type)
// Called from various places to output formatted debug information.
// param_1 is unused in this function; it may be a channel/context in caller.

void debugPrintCommand(int param_1, int msg)
{
    int cmdType;  // type at msg+4
    int data;     // temporary for dereferenced data

    // Print individual bits of the command type? (low 4 bits)
    debugPrintBool(*(byte *)(msg + 4) & 1);                     // bit0
    debugPrintBool((*(uint *)(msg + 4) >> 1) & 0xffffff01);     // bit1 (likely (type>>1)&1 but masked with 0xffffff01)
    debugPrintBool((*(uint *)(msg + 4) >> 2) & 0xffffff01);     // bit2
    debugPrintBool((*(uint *)(msg + 4) >> 3) & 0xffffff01);     // bit3

    cmdType = *(int *)(msg + 4);
    switch (cmdType)
    {
    case 1:
    case 7:
        // Print a string? 0xa0 might be a type flag for string/float.
        debugPrintValue(0xa0, msg + 8);
        break;

    case 2:
        // Print boolean: indicates whether data at +8 is nonzero.
        debugPrintBool(*(int *)(msg + 8) != 0);
        break;

    case 3:
        // Print a single integer value (data at +8).
        data = *(int *)(msg + 8);
        debugPrintValue(0x20, &data);
        break;

    case 4:
        // Same as case 3.
        data = *(int *)(msg + 8);
        debugPrintValue(0x20, &data);
        break;

    case 5:
    case 6:
        // Print two integer values (data at +8 and +0xC).
        data = *(int *)(msg + 8);
        debugPrintValue(0x20, &data);
        data = *(int *)(msg + 0xC);
        debugPrintValue(0x20, &data);
        break;

    case 8:
        // Print three integer values (data at +8, +0xC, +0x10).
        data = *(int *)(msg + 8);
        debugPrintValue(0x20, &data);
        data = *(int *)(msg + 0xC);
        debugPrintValue(0x20, &data);
        data = *(int *)(msg + 0x10);
        debugPrintValue(0x20, &data);
        break;
    }
    return;
}