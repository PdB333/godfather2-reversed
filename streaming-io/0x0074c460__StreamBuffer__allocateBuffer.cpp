// FUNC_NAME: StreamBuffer::allocateBuffer
// Function at 0x0074c460: Allocates internal stream buffer and copies header data from allocated block when a specific flag is set.
// Offsets: +0xe4 = m_flags (bit 1 triggers allocation, bit 0x20 set after copy)
//          +0xe8 = m_bufferData (8 bytes, possibly two pointers or a 64-bit value)
//          +0xf0 = m_bufferSize (4 bytes)
// Calls: FUN_00471610 (getRequiredBaseSize), FUN_00721d70 (aligned allocate, e.g., EARSAllocator::allocate)

uint __fastcall StreamBuffer::allocateBuffer(void* this) {
    uint flags = *(uint*)((char*)this + 0xe4);
    uint checkFlag = flags >> 1; // Check original bit 1 (value >> 1) & 1

    if (checkFlag & 1) {
        int baseSize = FUN_00471610();                    // Get required base size
        void* buffer = FUN_00721d70(4, baseSize + 0x30, DAT_00e51920, 0); // Allocate with alignment=4, total size = baseSize+0x30

        if (buffer == nullptr) {
            return 0; // Failure: null pointer
        }

        // Copy 8 bytes from offset 0x14 of allocated block to this+0xe8
        *(uint64*)((char*)this + 0xe8) = *(uint64*)((char*)buffer + 0x14);
        // Copy 4 bytes from offset 0x1c of allocated block to this+0xf0
        *(uint32*)((char*)this + 0xf0) = *(uint32*)((char*)buffer + 0x1c);

        // Set flag bit 0x20 to mark buffer as initialized
        *(uint*)((char*)this + 0xe4) |= 0x20;

        return 1; // Success
    }

    return 1; // If condition not met, still succeeds? Original returns (puVar1>>8<<8)|1, but condition might always be entered? We'll return success.
}