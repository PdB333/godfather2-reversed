// FUNC_NAME: EARSString::getBuffer
char* __fastcall EARSString::getBuffer()
{
    // Structure definition (hypothetical, based on analysis):
    // Offset 0x00: uint32_t sizeOrOffset;   // For small strings: maybe inline length? For large strings: offset to data from dataPtr?
    // Offset 0x04: uint16_t unknown;
    // Offset 0x06: uint16_t signature;      // 0x25E3 = large/dynamic string, other = small/inline string
    // Offset 0x08: union {
    //                 char inlineBuffer[?]; // For small strings, data starts here
    //                 char* dataPtr;        // For large strings, pointer to heap data
    //              };
    // Size: at least 0x0C bytes (three ints)

    if (*(uint16_t*)((uint8_t*)this + 6) != 0x25E3)
    {
        // Small string: data is stored inline starting at offset 0x08
        return (char*)(this + 2);  // this is int*, so this+2 = offset 0x08
    }
    else
    {
        // Large string: data is (dataPtr + sizeOrOffset)
        if (this[0] != 0)  // sizeOrOffset is non-zero
        {
            return (char*)(this[2] + this[0]); // this[2] = value at offset 0x08 (dataPtr), this[0] = offset
        }
        else
        {
            // Empty string returns a fixed sentinel at 0x00E2E5D0
            return (char*)0x00E2E5D0;
        }
    }
}