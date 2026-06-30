// FUN_004aadd0: ThreadLocalData::setFieldValue(unsigned int)
void __thiscall ThreadLocalData::setFieldValue(int this, unsigned int value)
{
    // Access per-thread data via Thread Local Storage (TLS) slot 0
    // FS:0x2c points to TLS array; first entry (+0) is a pointer to a per-thread structure
    // The structure at offset +8 contains the base address of the large per-thread block
    // Then write value to offset (0x70 + this->m_dataOffset) within that block
    // The 'this' object holds a relative offset in its +0x18 field (m_dataOffset)
    int* tlsArray = *(int**)(__readfsdword(0x2c));                 // FS:0x2c -> TLS array pointer
    int* perThreadBase = *(int**)((char*)tlsArray + 0);            // First TLS slot: pointer to per-thread struct
    int* actualDataBlock = *(int**)((char*)perThreadBase + 8);     // +8: pointer to the actual data block
    int targetOffset = 0x70 + *(int*)(this + 0x18);                 // 0x70 base + per-instance offset
    *(int*)((char*)actualDataBlock + targetOffset) = value;         // Store the value
}