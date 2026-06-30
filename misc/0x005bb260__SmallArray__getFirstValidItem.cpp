// FUNC_NAME: SmallArray::getFirstValidItem
// Function at 0x005bb260: Returns the first non-zero element from a small array.
// Structure layout:
//   +0x00: byte count (number of elements, max 31)
//   +0x02: short validFlag (if zero, array is considered empty)
//   +0x04: int items[count] (array of integers)
// Returns 0 if no valid element found.
int __thiscall SmallArray::getFirstValidItem(void)
{
    byte *thisPtr = (byte *)this;
    short validFlag = *(short *)(thisPtr + 2);
    if (validFlag == 0) {
        return 0;
    }
    byte count = *thisPtr & 0x1f; // Mask to 5 bits (max 31)
    int numItems = 1 << count;    // Number of items (2^count, but count is small)
    // Actually, the code uses 1 << (byte & 0x1f) as the loop bound.
    // This is unusual: it treats the byte as a shift amount to get a count.
    // For typical usage, count is 0-31, so 1<<count gives 1 to 2^31.
    // But the loop iterates iVar3 from 0 to numItems-1.
    // This suggests the byte is actually a power-of-two count? Or it's a bitmask?
    // Given the context, it's likely a count of elements (0-31) stored directly,
    // but the decompiler shows 1 << (byte & 0x1f). Possibly the byte is a bit index
    // for a bitfield? But the loop iterates over an array of ints.
    // We'll keep the logic as decompiled.
    int *items = *(int **)(thisPtr + 4);
    for (int i = 0; i < numItems; i++) {
        if (items[i] != 0) {
            return items[i];
        }
    }
    return 0;
}