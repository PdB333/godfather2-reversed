// FUNC_NAME: StateMachine::initializeStateMachine

// Function at 0x005e7db0: Initializes a state machine object with default values and state entry array.
// Likely part of EA EARS engine behavior system (e.g., PlayerSM or NPC state machine).
// Uses __thiscall with 'this' in EAX.

void __thiscall StateMachine::initializeStateMachine(void)
{
    // This is the 'this' pointer (in_EAX)
    int* thisPtr = in_EAX;

    // Global constants for default parameters
    int defaultParam1 = DAT_00e2b1a4;   // e.g., some duration or priority
    int defaultParam2 = DAT_00e2b04c;   // e.g., some threshold
    int defaultParam3 = DAT_00e2b050;   // e.g., some flag

    // Initialize main object fields
    *(int*)(thisPtr + 0xC) = 0;            // +0x0C: stateId
    *(int*)(thisPtr + 0x10) = 0;           // +0x10: substateId
    *(int*)(thisPtr + 0x14) = -1;          // +0x14: parentState
    *(int*)(thisPtr + 0x68) = 0;           // +0x68: timer
    *(int*)(thisPtr + 0x6C) = 0;           // +0x6C: timeoutDuration
    *(char*)(thisPtr + 0x70) = 0;          // +0x70: active (bool)
    *(int*)(thisPtr + 0x64) = 1;           // +0x64: priority
    *(int*)(thisPtr + 0x74) = 1;           // +0x74: version
    *(int*)(thisPtr + 0x78) = 0;           // +0x78: flags
    *(int*)(thisPtr + 0x7C) = 0;           // +0x7C: loopCount
    *(char*)(thisPtr + 0x80) = 0;          // +0x80: hasAnim
    *(int*)(thisPtr + 0x98) = 0;           // +0x98: target
    *(char*)(thisPtr + 0x84) = 0;          // +0x84: interruptable
    *(int*)(thisPtr + 0x88) = defaultParam1; // +0x88: param1
    *(char*)(thisPtr + 0x85) = 0;          // +0x85: canTransition
    *(int*)(thisPtr + 0x8C) = defaultParam2; // +0x8C: param2
    *(int*)(thisPtr + 0x90) = defaultParam3; // +0x90: param3
    *(int*)(thisPtr + 0x94) = 0;           // +0x94: transitionId
    *(int*)(thisPtr + 0x9C) = 0;           // +0x9C: behaviorCost
    *(int*)(thisPtr + 0xA0) = 0;           // +0xA0: exitFlags

    // Call sub-initializer (maybe sets up vtable or other base)
    FUN_005e3130();

    // Initialize array of state entries starting at offset 0xE0
    // Each entry is 120 bytes (0x1E * 4), with two pointer bases:
    // piVar2 = start of entry (offset 0x00 from entry)
    // puVar1 = start of entry + 0x10 (offset 0x10 from entry)
    int* entryBase = (int*)(thisPtr + 0xE0);    // piVar2 start
    int* entryParamBase = (int*)(thisPtr + 0xF0); // puVar1 start

    // Number of entries = extraout_EDX + 4 (assume extraout_EDX came from previous call result, probably 0 for 4 entries)
    int numEntries = extraout_EDX + 4;
    for (int i = 0; i < numEntries; i++)
    {
        // Entry structure:
        // offset 0x00: entryId (int)
        // offset 0x04: nextState
        // offset 0x08: flags (byte)
        // offset 0x09: more flags
        // offset 0x0C: enabled (int =1)
        // offset 0x10: param4 (int)
        // offset 0x14: param5
        // offset 0x18: param6 (byte)
        // offset 0x1C: param7? Actually 0x1C is byte at offset? Let's continue

        // Write to entry using piVar2 (base at offset 0)
        entryBase[0] = extraout_EDX;               // +0x00: entryId
        entryBase[-3] = extraout_EDX;              // +0x04: nextState
        *(char*)&entryBase[-2] = (char)extraout_EDX; // +0x08: flags byte
        *(char*)((int)entryBase - 7) = (char)extraout_EDX; // +0x09: more flags
        entryBase[-1] = 1;                         // +0x0C: enabled

        // Now via puVar1 (base at offset 0x10)
        entryParamBase[0] = 0;                     // +0x10: param4
        entryParamBase[1] = 0;                     // +0x14: param5
        *(char*)&entryParamBase[2] = (char)extraout_EDX; // +0x18: param6 byte
        entryParamBase[3] = 1;                     // +0x1C: param7 (int =1)
        entryParamBase[4] = 0;                     // +0x20: param8
        entryParamBase[5] = 0;                     // +0x24: param9
        *(char*)&entryParamBase[6] = (char)extraout_EDX; // +0x28: param10 byte

        // More fields at higher offsets
        entryParamBase[0x12] = 100;                // +0x58? Actually offset 0x10+0x12*4 = 0x58? Let's compute: base 0x10, index 0x12 (18) -> offset 16+72=88 bytes from entry start? That is +0x58? Actually 0x10 + 0x48 = 0x58. Yes.
        // But later same index is overwritten, so this may be intentional.

        entryParamBase[0x18] = extraout_EDX;       // +0x70? index 24 -> offset 16+96=112 -> +0x70
        entryParamBase[0x19] = extraout_EDX;       // +0x74? index 25 -> offset 116 -> +0x74
        entryParamBase[0x14] = extraout_EDX;       // +0x60? index 20 -> offset 80+16=96 -> +0x60
        entryParamBase[0x15] = extraout_EDX;       // +0x64? index 21 -> offset 100 -> +0x64
        entryParamBase[0x16] = -1;                 // +0x68? index 22 -> offset 104 -> +0x68
        entryParamBase[0xc] = extraout_EDX;        // +0x40? index 12 -> offset 48+16=64 -> +0x40
        *(char*)&entryParamBase[7] = (char)extraout_EDX; // byte at index 7 -> offset 28+16=44 -> +0x2C
        entryParamBase[8] = defaultParam1;         // +0x30? offset 32+16=48 -> +0x30
        *(char*)((int)entryParamBase + 0x1d) = (char)extraout_EDX; // byte at offset 16+29=45 -> +0x2D
        entryParamBase[9] = defaultParam2;         // offset 36+16=52 -> +0x34
        entryParamBase[10] = defaultParam3;        // offset 40+16=56 -> +0x38
        entryParamBase[0xb] = extraout_EDX;        // offset 44+16=60 -> +0x3C
        entryParamBase[0xd] = extraout_EDX;        // offset 52+16=68 -> +0x44
        entryParamBase[0xe] = extraout_EDX;        // offset 56+16=72 -> +0x48
        entryParamBase[0xf] = defaultParam1;       // offset 60+16=76 -> +0x4C
        entryParamBase[0x10] = defaultParam1;      // offset 64+16=80 -> +0x50
        entryParamBase[0x11] = defaultParam1;      // offset 68+16=84 -> +0x54
        entryParamBase[0x12] = 100;                // overwrite earlier? +0x58
        entryParamBase[0x13] = extraout_EDX;       // offset 72+16=88 -> +0x58? Actually index 19 -> 76+16=92 -> +0x5C
        entryParamBase[0x17] = extraout_EDX;       // offset 92+16=108 -> +0x6C

        // Advance to next entry (each entry is 120 bytes = 0x1E * 4)
        entryBase += 0x1E;
        entryParamBase += 0x1E;
    }

    // Final call (likely sets up default state)
    FUN_005e7ee0();
}