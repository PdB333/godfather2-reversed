// FUNC_NAME: ThreatManager::hasActiveThreat
// Address: 0x007e80c0
// Role: Checks if any threat level in the manager exceeds a global threshold (DAT_01205224).
// The manager contains two arrays: a primary array of 69 threat entries (each 8 bytes) at offset +0x354,
// and a secondary array of 4 threat groups (each 120 bytes) starting at offset +0x57C.
// Each group contains 5 threat pairs (flag + value) with specific offsets.

char __thiscall ThreatManager::hasActiveThreat(ThreatManager* this)
{
    uint* threatArray;          // Base of primary threat array
    uint* groupBase;            // Base of current threat group (points 40 bytes into the group)
    uint index;                 // Loop counter
    char result;                // Return value (0 = no active threat, 1 = active threat found)

    result = 0;
    index = 0;
    threatArray = (uint*)((int)this + 0x354);   // Primary array of 69 entries (each 8 bytes)

    // Check primary array: iterate over every other uint (first of each pair)
    do {
        if (DAT_01205224 < *threatArray) {
            result = 1;
            break;
        }
        index = index + 1;
        threatArray = threatArray + 2;   // Skip second uint of the pair
    } while (index < 0x45);              // 69 iterations

    index = 0;
    groupBase = (uint*)((int)this + 0x5a4);   // Points 40 bytes into the first group

    // Check secondary array: 4 groups, each with 5 threat pairs
    while (true) {
        if (result != 0) {
            return result;
        }

        // Check 5 threat pairs in the current group.
        // Each pair: flag at offset X, value at offset X+16 (relative to groupBase - 40)
        // Offsets relative to groupBase:
        //   -10: flag1, -6: value1
        //   -4: flag2, 0: value2
        //   2: flag3, 6: value3
        //   8: flag4, 0xc: value4
        //   0xe: flag5, 0x12: value5
        if (((((groupBase[-10] != 0) && (DAT_01205224 < groupBase[-6])) ||
             ((groupBase[-4] != 0) && (DAT_01205224 < *groupBase))) ||
            ((groupBase[2] != 0) && (DAT_01205224 < groupBase[6]))) ||
           ((groupBase[8] != 0) && (DAT_01205224 < groupBase[0xc]))) {
            break;   // Active threat found
        }

        if ((groupBase[0xe] != 0) && (DAT_01205224 < groupBase[0x12])) {
            result = 1;
        }

        index = index + 5;              // Move to next group (5 pairs per group)
        groupBase = groupBase + 0x1e;   // Advance by 30 uints (120 bytes) to next group
        if (0x13 < index) {             // After 4 groups (index 0,5,10,15 -> 20 > 19)
            return result;
        }
    }

    return 1;
}