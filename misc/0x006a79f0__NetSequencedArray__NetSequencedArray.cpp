// FUNC_NAME: NetSequencedArray::NetSequencedArray

// 0x006a79f0 - Constructor for NetSequencedArray (likely TNL packet sequencing)
// param_2 = maxIndex (number of slots - 1)
// param_3 = some identifier (e.g., sequence start or channel ID)
// Offsets: +0 = pointer to internal struct (12 bytes), +1 = counter (0), +2 = maxIndex,
//          +3 = id, +4 = flags (0), +5 = second array pointer
void __thiscall NetSequencedArray::NetSequencedArray(uint maxIndex, int id)
{
    // Allocate internal struct (3 ints: likely header + array pointer)
    int *internalStruct = (int *)FUN_009c8e50(0xc);    // allocNew(12)
    if (internalStruct != (int *)0) {
        // Allocate first array (size = (maxIndex+1) * 4)
        // Stored at internalStruct+8 (offset 8 in struct)
        internalStruct[2] = (int)FUN_009c8e80((maxIndex + 1) * 4); // allocArray
    }

    // Store internal struct pointer
    thisPtr[0] = (int)internalStruct;

    // Initialize counters/state
    thisPtr[1] = 0;
    thisPtr[2] = maxIndex;
    thisPtr[3] = id;
    thisPtr[4] = 0;

    // Zero out first array
    uint i = 0;
    do {
        *(int *)(*(int *)(thisPtr[0] + 8) + i * 4) = 0;
        i = i + 1;
    } while (i <= maxIndex);

    // Allocate second array (same size, presumably for opposite direction or ACK tracking)
    thisPtr[5] = (int)FUN_009c8e80((maxIndex + 1) * 4); // allocArray
    return;
}