// FUN_004971f0: InputSlotManager::findMatchingSlotIndex
uint __fastcall InputSlotManager::findMatchingSlotIndex(void* thisPtr, uint matchValue)
{
    uint idx;
    uint cmpVal;
    char type;
    uint result;

    // Local array: likely misinterpreted by decompiler; actual structure offset unknown.
    // byte slotValues[11]; // Uninitialized in this version, but might be part of the object.
    byte slotValues[11]; // Stack variable (decompiled as abStack_f)

    idx = 0;
    while (true) {
        type = *(byte *)((int)thisPtr + 8); // Object type at offset +0x8
        if ((type == 0x01) || (type == 0x03)) {
            cmpVal = (uint)slotValues[idx]; // Uses local array (likely structure member)
        } else {
            cmpVal = 0xff; // Default invalid value
        }

        if ((cmpVal == matchValue) && (cmpVal != 0xff) && (cmpVal != 0xfe)) {
            break;
        }

        idx++;
        if (idx > 1) {
            return 0xffffffff; // Not found
        }
    }

    return idx; // Returns 0 or 1
}