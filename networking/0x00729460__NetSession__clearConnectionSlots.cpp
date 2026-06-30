// FUNC_NAME: NetSession::clearConnectionSlots
// This function iterates over 64 connection slots (each 40 bytes) starting at offset 0x0 of this,
// clearing them and releasing any referenced objects.
// The slot structure (40 bytes):
//   +0x0: vtable pointer (set to global base vtable PTR_LAB_00e2f0c0)
//   +0x8: pointer to a sub-object (if non-null, released via FUN_004daf90)
// The loop processes slots in reverse order from the end of the array (this + 0xa00) backwards.

void __thiscall NetSession::clearConnectionSlots(int this) {
    int slotIndex = 0x3F; // 63 (64 slots total)
    int* currentSlotEnd = (int*)(this + 0xA00); // Points one past the last slot

    do {
        // Check if the sub-object pointer at slot offset +0x8 exists
        if (currentSlotEnd[-8] != 0) {
            // Release the sub-object (likely a destructor or decrement refcount)
            FUN_004daf90(currentSlotEnd[-8]);
        }

        // Set the vtable pointer at slot offset +0x0 to the global base class vtable
        currentSlotEnd[-10] = (int)&PTR_LAB_00e2f0c0;

        // Move back to the previous slot (40 bytes = 10 ints)
        currentSlotEnd -= 10;
        slotIndex--;
    } while (slotIndex >= 0);

    return;
}