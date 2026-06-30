// FUNC_NAME: ThreadLocalStorage::readSlot

// Function at 0x00556100: Reads a 0x17-byte data block from thread-local storage at a given slot index.
// param_1 points to a struct: { void* destBuffer; int unknown; int slotIndex; }
// If slotIndex >= 0, it retrieves the TLS base pointer using the global TLS index (DAT_01139810),
// then copies 0x17 bytes from offset (slotIndex << 6) into destBuffer.

void __thiscall ThreadLocalStorage::readSlot(void* thisPtr)
{
    // thisPtr is actually a pointer to a struct with fields:
    // +0x00: void* destBuffer
    // +0x04: int unused
    // +0x08: int slotIndex
    int* fields = (int*)thisPtr;
    int slotIndex = fields[2]; // +0x08
    if (slotIndex >= 0)
    {
        void* tlsBase = TlsGetValue(DAT_01139810); // global TLS index
        // Copy 0x17 bytes from tlsBase + (slotIndex << 6) to destBuffer
        FUN_00aa26e0(fields[0], slotIndex << 6, 0x17);
    }
}