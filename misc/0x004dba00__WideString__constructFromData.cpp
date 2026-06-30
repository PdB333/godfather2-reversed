// FUNC_NAME: WideString::constructFromData
void __thiscall WideString::constructFromData(int* thisPtr, void* sourceData, uint charCount)
{
    if (charCount != 0)
    {
        // Set character count and byte length (excluding null terminator)
        thisPtr[1] = charCount;                // +0x04: m_charCount
        thisPtr[2] = charCount * 2;            // +0x08: m_byteLength

        // Allocate buffer for (charCount + 1) wide characters 
        // (handles potential negative values via sign handling)
        uint allocSize = ((charCount & 0x7fffffff) + 1) * 2; // (charCount + 1) * 2 bytes
        wchar_t* buffer = (wchar_t*)allocateMemory((int)allocSize);

        // Store buffer pointer
        thisPtr[0] = (int)buffer;               // +0x00: m_data

        // Copy the wide character data from source
        memcpy(buffer, sourceData, thisPtr[1] * 2);

        // Null-terminate the string
        buffer[thisPtr[1]] = L'\0';             // *(undefined2*)(*thisPtr + thisPtr[1]*2) = 0

        // Store the deallocation function pointer
        thisPtr[3] = (int)deallocateMemory;     // +0x0C: m_deallocFunc
        return;
    }

    // If charCount is zero, set all fields to null/zero
    thisPtr[0] = 0;  // m_data
    thisPtr[2] = 0;  // m_byteLength
    thisPtr[1] = 0;  // m_charCount
    // Note: m_deallocFunc is not initialized in this case (remains unchanged or default?)
}