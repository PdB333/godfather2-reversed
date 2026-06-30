// FUNC_NAME: StreamWriter::writeEntityUpdate
void StreamWriter::writeEntityUpdate(uint32_t field1, uint32_t field2,
                                     const float* floatArray, int floatCount, int floatAlign,
                                     const Vector3* vec3Array, int vec3Count, int vec3Align,
                                     const Vector2* vec2Array, int vec2Count, int vec2Align,
                                     uint16_t finalData)
{
    // m_writePtr is a pointer to the current write position, stored at +0x14
    int*& m_writePtr = *(int**)((char*)this + 0x14);

    // Write header fields
    *(uint32_t*)m_writePtr = field1;
    m_writePtr += 4;
    *(uint32_t*)m_writePtr = field2;
    m_writePtr += 4;

    // Write float array metadata
    *(int*)m_writePtr = floatCount;
    m_writePtr += 4;
    *(int*)m_writePtr = floatAlign;
    m_writePtr += 4;

    // Align and copy float array (each float is 4 bytes)
    m_writePtr = (int*)((int)(m_writePtr) + floatAlign - 1) & ~(floatAlign - 1);
    _memcpy(m_writePtr, floatArray, floatCount * 4);
    m_writePtr += floatCount * 4;

    // Write Vector3 array metadata (each Vector3 is 12 bytes)
    *(int*)m_writePtr = vec3Count;
    m_writePtr += 4;
    *(int*)m_writePtr = vec3Align;
    m_writePtr += 4;
    m_writePtr = (int*)((int)(m_writePtr) + vec3Align - 1) & ~(vec3Align - 1);
    _memcpy(m_writePtr, vec3Array, vec3Count * 12);
    m_writePtr += vec3Count * 12;

    // Write Vector2 array metadata (each Vector2 is 8 bytes)
    *(int*)m_writePtr = vec2Count;
    m_writePtr += 4;
    *(int*)m_writePtr = vec2Align;
    m_writePtr += 4;
    m_writePtr = (int*)((int)(m_writePtr) + vec2Align - 1) & ~(vec2Align - 1);
    _memcpy(m_writePtr, vec2Array, vec2Count * 8);
    m_writePtr += vec2Count * 8;

    // Write final 2-byte field and align to 4-byte boundary
    *(uint16_t*)m_writePtr = finalData;
    m_writePtr = (int*)(((int)m_writePtr + 5) & 0xFFFFFFFC);
}