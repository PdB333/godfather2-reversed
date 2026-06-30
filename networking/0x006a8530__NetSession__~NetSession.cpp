// FUNC_NAME: NetSession::~NetSession
void __fastcall NetSession::~NetSession(NetSession* this)
{
    // Iterate over 32 slots (each 12 bytes) starting from the last slot at offset 0x180
    // Slots are stored as an array of 12-byte structures beginning at offset 0x0C
    int* slotStart;
    int* slotPtr = reinterpret_cast<int*>(this) + 99; // +0x18C (start of last slot + 12)
    int slotIndex = 31;

    do {
        slotStart = slotPtr - 3; // Point to the beginning of the current slot (offset -12 bytes)
        slotPtr = slotPtr - 3;   // Move to the previous slot
        if (*slotStart != 0) {
            // Free the slot object if its first pointer is non-null
            destroySlot(slotPtr); // FUN_004daf90
        }
        slotIndex--;
    } while (slotIndex >= 0);

    // Set vtable to purecall (base class destructor marker)
    *reinterpret_cast<void**>(this) = &PTR___purecall_00e407a4;
}