// FUNC_NAME: SomeManager::getSizeForType
// Function address: 0x00669d40
// Role: Computes the size of a data structure based on a type identifier.
//   Handles special case for type == 2 by calculating bit length from a bitmask.
//   For other types (0-62), uses an external helper to iterate over elements.
//   Returns 0 for invalid types or on failure.

int SomeManager::getSizeForType(int type) {
    int* thisPtr; // in_EAX - this pointer, assumed to be a struct
    uint bitfield;
    int iVar1;
    int iVar3;
    bool bVar4;
    int local10[2]; // Possibly a pair of pointers or handles
    int local8; // Used as a flag, likely initialized elsewhere or a register alias

    iVar1 = type;
    if (type == 2) {
        // Type 2 is special: compute size based on a bitmask
        thisPtr = /* assumed from EAX */?;
        iVar1 = *thisPtr; // Field +0x00: count or value
        if (iVar1 == 0) {
            // No entries, base size depends on flag at +0x08
            return (thisPtr[2] == 1) + 1; // Base size: 1 or 2
        }
        // Compute bit length from a bitmask stored in an array at thisPtr[3] (+0x0C)
        iVar3 = iVar1 * 28 - 28; // (count - 1) * 28
        // Get the bitmask from an array: thisPtr[3] + (iVar1-1)*4
        bitfield = *(uint*)(thisPtr[3] + -4 + iVar1 * 4);
        // Count number of bits (position of highest set bit)
        while (bitfield != 0) {
            iVar3 += 1;
            bitfield >>= 1;
        }
        // Final size = base + bit length
        return (thisPtr[2] == 1) + 1 + iVar3;
    }

    // For other types: ensure type is <= 62 (0x3E)
    if ((uint)(type - 2) > 62) {
        return 0;
    }

    // Call external validation function; if non-zero, return 0
    iVar3 = FUN_006677e0(); // Possibly validates manager state
    if (iVar3 != 0) {
        return 0;
    }

    // Use local8 as a flag (perhaps originally from thisPtr[?])
    bVar4 = (local8 == 1);
    if (bVar4) {
        local8 = 0;
    }
    uint uVar2 = (uint)bVar4; // Starting count offset

    // Iterate over elements using an external iterator function
    while (true) {
        if (local10[0] == 0) {
            // No more elements? Call cleanup and return count
            FUN_00665b40(); // Cleanup function
            return uVar2 + 1;
        }
        // Call iterator function: FUN_00666670(local10, type, local10, &type)
        // Seems to advance and possibly check conditions
        iVar3 = FUN_00666670(local10, iVar1, local10, &type);
        if (iVar3 != 0) break;
        uVar2 += 1;
    }

    // Break on iterator returning non-zero (error or found)
    FUN_00665b40(); // Cleanup
    return iVar3;
}