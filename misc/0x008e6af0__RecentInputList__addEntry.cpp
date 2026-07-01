// FUNC_NAME: RecentInputList::addEntry
// Function address: 0x008e6af0
// Role: Adds a 16-byte element to a bounded list (max 12 entries), growing the internal array if necessary.
// The list likely stores recent input events or similar small fixed-size records.

void __thiscall RecentInputList::addEntry(void *thisPtr, const InputEntry *entry) // InputEntry is 16 bytes (4 ints/floats)
{
    int capacity = *(int *)((int)thisPtr + 0x54);
    int count = *(int *)((int)thisPtr + 0x50);

    // Grow array if full
    if (count == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        FUN_008defe0(capacity); // Reallocate internal array to new capacity (size in elements)
        // After reallocation, capacity and data pointer (at +0x4c) are updated by the helper.
    }

    // Compute pointer to next slot (each slot is 0x10 = 16 bytes)
    InputEntry *slot = (InputEntry *)(*(int *)((int)thisPtr + 0x4c) + count * 0x10);
    count++; // Increment count
    *(int *)((int)thisPtr + 0x50) = count;

    if (slot != nullptr) {
        *slot = *entry; // Copy 16 bytes (4 int32)
    }

    // Enforce maximum of 12 entries by removing oldest if exceeded
    // FUN_008e5e60(0) likely pops the first element and decreases count.
    uint currentCount = *(uint *)((int)thisPtr + 0x50);
    while (currentCount > 0xc) {
        FUN_008e5e60(0); // Remove first element (argument 0 might indicate direction)
        currentCount = *(uint *)((int)thisPtr + 0x50);
    }

    return;
}