// FUNC_NAME: ResourceArray::clear
// Address: 0x0090c670
// Role: Clears a fixed-size resource array (6 slots) with a usage count.

void __fastcall ResourceArray::clear(int this)
{
    uint *countPtr;
    uint *slotPtr;
    uint i;
    uint current;

    // Loop: call FUN_004df600 for each element up to the current count
    countPtr = (uint *)(this + 0x18);
    if (*(int *)(this + 0x18) != 0) {
        i = 0;
        do {
            FUN_004df600();  // Process/release each object (no arguments, likely relies on global state or this)
            i = i + 1;
        } while (i < *countPtr);
    }
    *countPtr = 0;  // Reset count

    // Clear the 6 pointer slots (offsets 0x00, 0x04, 0x08, 0x0C, 0x10, 0x14)
    // For each non‑null pointer, zero the field at offset +8, then zero the pointer.
    int slotIdx = 5;
    do {
        slotPtr = countPtr - 1;  // countPtr is decremented each iteration
        countPtr = countPtr - 1;
        current = *slotPtr;
        if (current != 0) {
            *(undefined4 *)(current + 8) = 0;  // Set some field (e.g., reference count, next pointer) to 0
            *slotPtr = 0;                      // Clear the pointer itself
        }
        slotIdx = slotIdx - 1;
    } while (-1 < slotIdx);

    return;
}