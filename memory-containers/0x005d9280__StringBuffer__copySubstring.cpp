//FUNC_NAME: StringBuffer::copySubstring
// Function address: 0x005d9280
// Copies a substring from the internal source buffer to the destination buffer,
// null-terminates, and updates the copied length and original start index.
// The element size is 1 byte (char) or 2 bytes (wchar_t) based on m_isWideChar.

int StringBuffer::copySubstring(void)
{
    // 'this' pointer in ESI, accessed as int* for field offsets
    int* thisPtr = reinterpret_cast<int*>(this);

    // Determine element size: 1 for char, 2 for wchar_t
    size_t elementSize = 1;
    if (*(char*)(thisPtr + 2) != '\0') { // m_isWideChar at offset +0x08
        elementSize = 2;
    }

    // Source pointer: m_source + m_startIndex * elementSize
    void* src = reinterpret_cast<void*>(
        *thisPtr * elementSize + *(thisPtr + 3) // m_startIndex * elementSize + m_source
    );

    // Destination buffer at offset +0x14 (thisPtr[5])
    void* dst = reinterpret_cast<void*>(thisPtr[5]); // m_dest

    // Number of elements to copy: m_length at offset +0x04 (thisPtr[1])
    size_t numElements = thisPtr[1]; // m_length
    size_t copySize = numElements * elementSize;

    // Copy the substring data
    _memcpy(dst, src, copySize);

    // Write null terminator at the end
    int nullTerminator = 0;
    _memcpy(
        reinterpret_cast<void*>(numElements * elementSize + reinterpret_cast<size_t>(dst)),
        &nullTerminator,
        elementSize
    );

    // Update metadata fields
    thisPtr[7] = *thisPtr;          // m_originalStart = m_startIndex
    thisPtr[6] = thisPtr[1];        // m_copiedLength = m_length

    // Return pointer to the destination buffer
    return thisPtr[5]; // m_dest
}