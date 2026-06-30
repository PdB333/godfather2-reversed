// FUNC_NAME: GameStateManager::applyStateTransition
// Function at 0x0051fc90 - manages game state transitions, likely for starting/stopping a game phase (e.g., combat, building takeover)
// Sets global state variables (DAT_ prefixed) indicating current scene timings, flags, and object lists.
void __thiscall GameStateManager::applyStateTransition(bool isEnteringState)
{
    // The 'this' pointer (in_EAX) points to a game state info block (#)
    ushort flags;      // This->flags at +0x44
    int *thisPtr;      // The raw this pointer
    int index;         // Temporary
    uint clampedVal1, clampedVal2; // For clamping score/state globals
    uint stateVal;      // Derived state value
    uint returnCode;    // uVar4
    int *listIter;     // Iterator for object lists
    uint temp7;        // Temporary

    // Assume in_EAX is the 'this' pointer
    // The actual code uses *in_EAX which suggests the first field is a pointer to self? 
    // But in typical __thiscall, in_EAX is 'this'. Here it's dereferenced as *in_EAX, 
    // so likely the object's first field is a pointer to some data structure.
    // Let's treat *in_EAX as the main data pointer.
    int *dataPtr = *(int**)this; // Equivalent to *in_EAX
    if (dataPtr == 0) return;

    flags = *(ushort *)(dataPtr + 0x44 / 4); // flags at +0x44

    uint local_28 = 1; // local_28

    if (!isEnteringState)
    {
        if (flags & 0x400) return; // Already in a specific sub-state?
        if (flags & 0x200) local_28 = 0; // Some condition to disable something
    }
    else
    {
        if (!(flags & 0x200)) return; // Must have flag 0x200 to enter
    }

    if (!isEnteringState)
    {
        // Determine animation/state type
        stateVal = 0;
        // Check sign of lower byte? (char)uVar1 < 0 means MSB set
        if ((signed char)(flags & 0xFF) < 0)
            stateVal = 2;
        else if (flags & 0x20)
            stateVal = 1;
        FUN_0053b1e0(stateVal); // Submit state change to another system
    }
    else
    {
        // Entering state - initialize global state variables
        DAT_01125380 = 0;
        DAT_01125384 = 0;
        DAT_01125388 = 2; // Index into some table

        if (thisPtr[3] == 0) // thisPtr+12 (some object pointer)
        {
            DAT_0112537c = 4;
            DAT_01125389 = 0x13; // Table index 19
            DAT_011252e8 = DAT_01125394;
            DAT_011252ec = DAT_011253e4;
        }
        else if (!(flags & 0x4000))
        {
            DAT_0112537c = 5;
            DAT_01125389 = 0x14; // 20
            DAT_011252e8 = DAT_01125394;
            DAT_011252ec = DAT_011253e8;
        }
        else
        {
            DAT_0112537c = 6;
            DAT_01125389 = 0x15; // 21
            DAT_011252e8 = DAT_01125394;
            DAT_011252ec = DAT_011253ec;
        }
    }

    // Set global pointer to a static struct PTR_PTR_011252d8
    DAT_012058e8 = &PTR_PTR_011252d8;
    FUN_0060a460(DAT_011252e8);  // Possibly increment ref count or lock
    FUN_0060a460(DAT_011252ec);
    FUN_0053b320(); // Perform some system update

    // Check another flag bit to choose between two modes
    if (!(*(ushort*)(dataPtr + 0x44) & 0x1000))
    {
        // Mode A: set global timers to 22 and state to 3
        if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16; // min clamp to 22
        if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16; // max clamp to 22
        _DAT_011f3a30 = 3;
    }
    else
    {
        // Mode B: set global timers to 22 and state to 1
        if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16;
        if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16;
        _DAT_011f3a30 = 1;
    }

    FUN_00417cf0(1, 5, 6); // Possibly set some global state flags

    // Set global timer array indices and values (multiple clamps)
    // These appear to be settings for a state machine with multiple slots

    // Slot 7: 
    if (DAT_012058d0 < 7) DAT_012058d0 = 7;
    if (7 < DAT_00f15988) DAT_00f15988 = 7;
    _DAT_011f39f4 = 1;

    // Slot 0xe (14):
    if (DAT_012058d0 < 0xe) DAT_012058d0 = 0xe;
    if (0xe < DAT_00f15988) DAT_00f15988 = 0xe;
    _DAT_011f3a10 = 1;

    FUN_0041e660(_DAT_00e2d7d4, _DAT_00e2d7d8); // Update some system?

    // Slot 0x19 (25):
    if (DAT_012058d0 < 0x19) DAT_012058d0 = 0x19;
    if (0x19 < DAT_00f15988) DAT_00f15988 = 0x19;
    _DAT_011f3a3c = 5;

    // Slot 0x18 (24):
    if (DAT_012058d0 < 0x18) DAT_012058d0 = 0x18;
    if (0x18 < DAT_00f15988) DAT_00f15988 = 0x18;
    _DAT_011f3a38 = 0;

    // Slot 0xf (15):
    if (DAT_012058d0 < 0xf) DAT_012058d0 = 0xf;
    if (0xf < DAT_00f15988) DAT_00f15988 = 0xf;
    _DAT_011f3a14 = 0;

    // Manage memory for lists (thisPtr[3], [4] are object arrays)
    if (thisPtr[3] != 0)
        FUN_00606e60(thisPtr[3], 0x300000); // Set memory size or flags
    if (thisPtr[4] != 0)
        FUN_00606e60(thisPtr[4], 0x3034000);

    // Use table at DAT_01125389 * 0x3c + 0x11254bc to get data pointer
    index = ((uint)DAT_01125389) * 0x3c;
    index += 0x11254bc;
    int *tableData = *(int**)index;
    if (tableData != 0)
    {
        FUN_0060add0(DAT_011252ec, tableData, &DAT_011f6680); // Add data to list
    }

    if (isEnteringState)
    {
        FUN_0053b3e0(thisPtr[4]); // Extra initialization
    }

    FUN_0053bb60(DAT_012058f4); // Process/sync something

    if (*(byte *)(dataPtr + 0x44) & 0x80) // Check flag 0x80
    {
        FUN_0053b4f0(); // Call additional function
    }

    // Read position/vector from dataPtr +0x78..0x80
    uint vecX = *(uint*)(dataPtr + 0x78);
    uint vecY = *(uint*)(dataPtr + 0x7c);
    uint vecZ = *(uint*)(dataPtr + 0x80);
    local_20 = vecX;
    local_1c = vecY;
    local_18 = vecZ;
    // Use table at DAT_01125388 * 0x38 + 0x11253f0
    index = ((uint)DAT_01125388) * 0x38;
    index += 0x11253f0;
    int *tableData2 = *(int**)index;
    local_14 = DAT_00e2b1a4;
    if (tableData2 != 0)
    {
        FUN_0060add0(DAT_011252e8, tableData2, &local_20); // Add vector data to list
    }

    // Another clamp and set
    if (DAT_012058d0 < 0xe) DAT_012058d0 = 0xe;
    if (0xe < DAT_00f15988) DAT_00f15988 = 0xe;
    _DAT_011f3a10 = 0;

    if (!isEnteringState)
    {
        // Exiting state: set some conditional based on dataPtr+0x48
        FUN_00417fe0(*(char*)(dataPtr + 0x48) != 3);
        FUN_004ec7a0(); // Additional exit logic
    }
    else
    {
        // Entering state: set something
        FUN_00417fe0(1);
        if (!(*(ushort*)(dataPtr + 0x44) & 0x800))
        {
            // No specific flag: call with parameters derived from flags and constants
            FUN_00417db0(5, 6, 1, 0xe, 6);
            // local_24 = concatenation of something
            // local_24 = (local_24 & 0x00FFFFFF) | (*(byte*)(dataPtr+0x46) << 24)
            uint local_24 = (local_24 & 0x00FFFFFF) | ((uint)*(byte*)(dataPtr + 0x46) << 24);
            FUN_00417f00(local_24, local_24, local_24, local_24);
        }
        else
        {
            FUN_00417db0(5, 6, 1, 1, 2);
        }
    }

    //----------------- Continued from truncated decompile --------------------
    // More clamps and function calls

    // ... (I'll continue with the rest from the full decompile)

    // ... After the if-else block, there are more clamps:

    // Slot 0x19 again:
    if (DAT_012058d0 < 0x19) DAT_012058d0 = 0x19;
    if (0x19 < DAT_00f15988) DAT_00f15988 = 0x19;
    _DAT_011f3a3c = 5;

    // Slot 0x18:
    if (DAT_012058d0 < 0x18) DAT_012058d0 = 0x18;
    if (0x18 < DAT_00f15988) DAT_00f15988 = 0x18;
    _DAT_011f3a38 = (uint)*(byte*)(dataPtr + 0x49);

    // Slot 0xf:
    if (DAT_012058d0 < 0xf) DAT_012058d0 = 0xf;
    if (0xf < DAT_00f15988) DAT_00f15988 = 0xf;
    _DAT_011f3a14 = (uint)(*(byte*)(dataPtr + 0x49) != 0);

    FUN_0053ba20(); // Some system update
    FUN_0053bab0(0); // Pass zero

    // local_24 update: combine with half of thisPtr[0xd]
    local_24 = (local_24 & 0x00FFFFFF) | ((thisPtr[0xd] >> 1) & 0xFF) << 24;
    local_24 &= 0xFFFFFF01; // Clear bit 0? Actually bit 0 cleared.

    // Conditional list processing based on global flags
    if (DAT_012054eb == 0)
    {
        if (thisPtr[2] != 0)
            FUN_00606e60(thisPtr[2], 0x3034000);
        FUN_0053b420(thisPtr[3]);
        // Iterate over list from thisPtr[5] to thisPtr[7]
        listIter = (int*)thisPtr[5];
        if (listIter != (int*)thisPtr[7])
        {
            do {
                (**(code**)(*listIter + 0xc))(local_28, isEnteringState, local_24, 0x3f800000);
                listIter = (int*)listIter[0x10];
            } while (listIter != (int*)thisPtr[7]);
        }
    }

    if (DAT_012054fc == 0)
    {
        if (thisPtr[2] != 0)
            FUN_00606e60(thisPtr[2], 0x3334000);
        FUN_0053b420(thisPtr[3]);
        // Another clamp
        if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16;
        if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16;
        _DAT_011f3a30 = 1;
        // Iterate over list from thisPtr[8] to thisPtr[10]
        listIter = (int*)thisPtr[8];
        if (listIter != (int*)thisPtr[10])
        {
            do {
                (**(code**)(*listIter + 0xc))(local_28, isEnteringState, local_24, 0x3f800000);
                listIter = (int*)listIter[0x10];
            } while (listIter != (int*)thisPtr[10]);
        }
    }

    if (thisPtr[2] != 0)
        FUN_00606e60(thisPtr[2], 0x3034000);
    if (thisPtr[3] != 0)
        FUN_00606e60(thisPtr[3], 0x3034000);

    // More final clamps and state settings
    clampedVal1 = DAT_012058d0;
    clampedVal2 = DAT_00f15988;

    if (_DAT_01125378 != 0)
    {
        temp7 = _DAT_01125378 & 0xff;
        if ((&DAT_011eb8fc)[DAT_011252ec * 0x10] != 0)
            temp7 += 0x10;
        FUN_00618d40();
        clampedVal1 = DAT_012058d0;
        clampedVal2 = DAT_00f15988;
        (&DAT_011d912c)[temp7] = 0;
    }

    DAT_012058e8 = 0;
    DAT_012058f0 = 0;

    // Final set of clamps
    if (clampedVal1 < 0x1b) { clampedVal1 = 0x1b; DAT_012058d0 = 0x1b; }
    if (clampedVal2 > 0x1a) { clampedVal2 = 0x1b; DAT_00f15988 = 0x1b; }
    _DAT_011f3a44 = 0;

    if (clampedVal1 < 0x19) { clampedVal1 = 0x19; DAT_012058d0 = 0x19; }
    if (clampedVal2 > 0x19) { clampedVal2 = 0x19; DAT_00f15988 = 0x19; }
    _DAT_011f3a3c = 7;

    if (clampedVal1 < 0x18) { clampedVal1 = 0x18; DAT_012058d0 = 0x18; }
    if (clampedVal2 > 0x18) { clampedVal2 = 0x18; DAT_00f15988 = 0x18; }
    _DAT_011f3a38 = 0;

    if (clampedVal1 < 0xf) { clampedVal1 = 0xf; DAT_012058d0 = 0xf; }
    if (clampedVal2 > 0xf) { clampedVal2 = 0xf; DAT_00f15988 = 0xf; }
    _DAT_011f3a14 = 0;

    if (clampedVal1 < 0xe) { clampedVal1 = 0xe; DAT_012058d0 = 0xe; }
    if (clampedVal2 > 0xe) { clampedVal2 = 0xe; DAT_00f15988 = 0xe; }
    _DAT_011f3a10 = 1;

    if (clampedVal1 < 7) { clampedVal1 = 7; DAT_012058d0 = 7; }
    if (clampedVal2 > 7) { clampedVal2 = 7; DAT_00f15988 = 7; }
    _DAT_011f39f4 = 1;

    if (clampedVal1 < 0x16) DAT_012058d0 = 0x16;
    if (clampedVal2 > 0x16) DAT_00f15988 = 0x16;
    _DAT_011f3a30 = 1;

    FUN_00417cf0(1, 5, 6);
    FUN_0041e660(0, 0);
}