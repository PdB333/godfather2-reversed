// FUNC_NAME: SmallPairArray::insertAt
// Function address: 0x0083b820
// Inserts a pair (two 32-bit values) at a given index in a fixed-size array of 4 elements.
// Object layout:
//   +0x00: array[4] of struct { uint32_t first; uint32_t second; } (8 bytes each)
//   +0x28: uint32_t count (number of valid elements, 0-4)
// Returns: low byte = 1 on success, high 24 bits = (second value >> 8) (unused?), or error if count > 4.

uint __thiscall SmallPairArray::insertAt(int thisPtr, uint32_t* newPair, uint index)
{
    uint count = *(uint*)(thisPtr + 0x28);
    uint32_t* array = (uint32_t*)thisPtr; // array starts at offset 0

    // If already full (count > 4), return error (count masked)
    if (count > 4) {
        return count & 0xffffff00;
    }

    if (index != count) {
        // Inserting in the middle: shift elements down from the end to make room
        // First, copy the last element one slot forward (to the next position)
        *(uint32_t*)(thisPtr + count * 8) = *(uint32_t*)(thisPtr + (count - 1) * 8);
        *(uint32_t*)(thisPtr + 4 + count * 8) = *(uint32_t*)(thisPtr + 4 + (count - 1) * 8);
        count = *(int*)(thisPtr + 0x28) - 1; // decrement count for shifting loop

        // Shift elements from count-1 down to index+1
        if (index < count) {
            uint32_t* src = (uint32_t*)(thisPtr + count * 8);
            int numToShift = count - index;
            do {
                src[0] = src[-2];
                src[1] = src[-1];
                src -= 2;
                numToShift--;
            } while (numToShift != 0);
        }

        // Update count (increment after shifting)
        *(int*)(thisPtr + 0x28) = *(int*)(thisPtr + 0x28) + 1;
    }

    // Write the new pair at the target index
    *(uint32_t*)(thisPtr + index * 8) = newPair[0];
    uint32_t secondVal = newPair[1];
    *(uint32_t*)(thisPtr + 4 + index * 8) = secondVal;

    // If index == count (append), increment count
    if (index == count) {
        *(int*)(thisPtr + 0x28) = *(int*)(thisPtr + 0x28) + 1;
    }

    // Return success with high bits from second value
    return (secondVal >> 8) | 1;
}