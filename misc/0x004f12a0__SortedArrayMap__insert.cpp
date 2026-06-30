// FUNC_NAME: SortedArrayMap::insert
// Address: 0x004f12a0
// Role: Insert a key-value pair into a sorted array map.
// The array is stored as a flat list of (key, value) pairs (8 bytes each).
// Global pointers: 
//   DAT_01218f28 -> base of array (uint*)
//   DAT_01218f2c -> current count (uint)
//   DAT_01218f30 -> capacity (uint)

void __cdecl SortedArrayMap::insert(uint key, uint value)
{
    uint currentCount = DAT_01218f2c;
    uint index = 0;

    if (currentCount != 0) {
        do {
            uint currentKey = *(uint *)(DAT_01218f28 + index * 8);
            if (currentKey == key) {
                break; // Duplicate key, do nothing
            }
            if (key <= currentKey && currentKey != key) {
                // Key is less than currentKey, need to insert before this position
                uint *newSlot = (uint *)FUN_004f1690(); // Allocates and shifts to make room
                newSlot[0] = key;
                newSlot[1] = value;
                break;
            }
            index++;
        } while (index < currentCount);
    }

    if (index == currentCount) {
        // Key greater than all existing keys, append at end
        if (currentCount == DAT_01218f30) {
            FUN_004f1460(); // Grow array
        }
        uint *endSlot = (uint *)(DAT_01218f28 + currentCount * 8);
        DAT_01218f2c = currentCount + 1;
        if (endSlot != NULL) {
            endSlot[0] = key;
            endSlot[1] = value;
        }
    }
}