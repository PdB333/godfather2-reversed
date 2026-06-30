// FUNC_NAME: StringBuffer::extractSubstring
__thiscall void* StringBuffer::extractSubstring(void) {
    // Structure fields (offsets relative to this):
    // +0x00: int32 m_start (start index in elements)
    // +0x04: int32 m_count (number of elements to copy)
    // +0x08: char   m_isWide (0 = 1-byte chars, 1 = 2-byte chars)
    // +0x0C: void*  m_sourcePtr (source data)
    // +0x14: void*  m_destPtr (output buffer)
    // +0x18: int32  m_resultCount (stored count after extraction)
    // +0x1C: int32  m_resultStart (stored start after extraction)

    int32* thisInt = (int32*)this;
    size_t elementSize = 1;
    if (*((char*)thisInt + 8) != 0) {
        elementSize = 2;
    }

    // Copy the requested range from source to destination
    memcpy(
        (void*)thisInt[5],                          // destPtr
        (void*)(thisInt[3] + thisInt[0] * elementSize), // sourcePtr + start * elementSize
        thisInt[1] * elementSize                    // count * elementSize
    );

    // Append a zero terminator of the appropriate size
    uint32 null = 0;
    memcpy(
        (void*)(thisInt[5] + thisInt[1] * elementSize),
        &null,
        elementSize
    );

    // Store the original start and count for result tracking
    thisInt[7] = thisInt[0]; // resultStart = start
    thisInt[6] = thisInt[1]; // resultCount = count

    return (void*)thisInt[5];
}