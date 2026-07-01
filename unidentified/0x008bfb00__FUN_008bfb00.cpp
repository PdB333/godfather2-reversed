//FUNC_NAME: SomeClass::copyDataArray
// Address: 0x008bfb00
// Copies an array of 8-byte data elements from internal storage to an external buffer.
// Returns the total number of bytes copied (count * 8).

int __thiscall SomeClass::copyDataArray(SomeClass* this, uint32_t* outBuffer)
{
    // Offset +0x190: m_dataCount (uint32)
    uint32_t count = *(uint32_t*)((uint8_t*)this + 0x190);
    if (count != 0) {
        // Offset +0x18c: m_dataArray (pointer to array of 8-byte elements)
        uint8_t* dataArray = *(uint8_t**)((uint8_t*)this + 0x18c);
        for (uint32_t i = 0; i < count; i++) {
            // Each element is 8 bytes: two 32-bit values
            outBuffer[i * 2]     = *(uint32_t*)(dataArray + i * 8);
            outBuffer[i * 2 + 1] = *(uint32_t*)(dataArray + i * 8 + 4);
        }
    }
    return count * 8; // total bytes copied
}