// FUNC_NAME: EventQueue::push
void __thiscall EventQueue::push(uint32_t eventType, uint8_t flagsA, uint8_t flagsB, uint8_t flagsC, uint32_t data)
{
    // This function appends a 12-byte Event record to the internal dynamic array.
    // The array is stored as a buffer pointer at +0x70, count at +0x74, capacity at +0x78.
    // Each element is 12 bytes: [0-3] eventType (uint32), [4] flagsA (uint8), [5] flagsB (uint8), [6] flagsC (uint8), [8-11] data (uint32)
    // There is a 1-byte padding at offset +0x7.

    if (*(int *)(this + 0x74) == 0) {           // If count is 0 (i.e., during first push), defer to capacity check
        // intentionally left blank, just fall through to capacity check below
    }

    int count = *(int *)(this + 0x74);
    int capacity = *(int *)(this + 0x78);

    if (count == capacity) {
        // Resize: double capacity (or set to 1 if capacity was 0)
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // FUN_004ae860 is a realloc/resize function expecting the new capacity (in number of elements)
        FUN_004ae860(newCapacity);
    }

    // Pointer to the insertion slot
    Event *slot = (Event *)(*(int *)(this + 0x70) + count * 12);
    slot->eventType = eventType;
    slot->flagsA = flagsA;
    slot->flagsB = flagsB;
    slot->flagsC = flagsC;
    slot->data = data;

    // Increment count
    *(int *)(this + 0x74) = count + 1;

    // FUN_004ae6f0 is a post‑insertion notification (e.g., mark array dirty, trigger processing)
    FUN_004ae6f0();
}