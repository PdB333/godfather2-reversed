// FUNC_NAME: DataBuffer::initializeFromGlobal
void __fastcall DataBuffer::initializeFromGlobal(DataBuffer* this)
{
    // Check if buffer is already initialized (flag at offset +0x81)
    if (*(char*)((int)this + 0x81) == '\0') {
        // If the global source exists (likely a loaded resource pointer)
        if (DAT_0112f9c0 != 0) {
            // Copy 0x8000 bytes from global source into internal buffer at +0x4c
            // FUN_00408900 is likely a memory copy routine (memcpy)
            FUN_00408900((int)this + 0x4c, &DAT_0112f9c0, 0x8000);
        }
        // Mark buffer as initialized
        *(char*)((int)this + 0x81) = 1;
    }
}