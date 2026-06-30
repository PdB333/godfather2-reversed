// FUNC_NAME: EARSVariant::serializeToBuffer
void EARSVariant::serializeToBuffer(void* destBuffer, int* outSize) const
{
    // Copy first DWORD of this object to destination (likely a header or size field)
    *(int*)destBuffer = *(int*)this;

    // Type tags for primitive types (0x3afd3141 and 0x3e55ddf1 are unknown but likely represent integer/float variants)
    const int TYPE_FLOAT_OR_INT1 = 0x3afd3141; // Possible float variant
    const int TYPE_FLOAT_OR_INT2 = 0x3e55ddf1; // Possible int variant

    int typeTag = this->m_type; // Offset assumed +0x0C
    void* dataPtr = this->m_data; // Offset assumed +0x10

    // If type is not one of the known primitives and data field is null, treat as empty (8 bytes: header + padding)
    if (typeTag != TYPE_FLOAT_OR_INT1 && typeTag != TYPE_FLOAT_OR_INT2 && dataPtr == nullptr)
    {
        *outSize = 8; // 8 bytes total (header + zeroed second DWORD)
        ((int*)destBuffer)[1] = 0;
        return;
    }

    // Write pointer to data payload area (just after header and type fields)
    ((int*)destBuffer)[1] = (int)((int*)destBuffer + 2); // Points to after first two DWORDs (header and type)
    ((int*)destBuffer)[2] = typeTag;

    // If type is a variant that stores the value inline (4 bytes), write the data directly
    if (typeTag == TYPE_FLOAT_OR_INT1 || typeTag == TYPE_FLOAT_OR_INT2)
    {
        ((int*)destBuffer)[3] = *(int*)dataPtr; // Copy the value directly (assume dataPtr points to the value)
        *outSize = 0x10; // 16 bytes: header + type + value + padding?
        return;
    }

    // Otherwise, it's a blob/String: copy data and pad to 4-byte alignment
    int* dstData = (int*)((int*)destBuffer + 4); // Points after the first 4 DWORDs (16 bytes)
    ((int*)destBuffer)[3] = (int)dstData; // Store pointer to data in output buffer (flattened)

    memcpy(dstData, dataPtr, this->m_dataSize); // Copy the actual data (size at +0x04)

    // Align to next DWORD boundary
    void* afterData = (char*)dstData + this->m_dataSize;
    void* aligned = (void*)((int)afterData + (4 - ((uint)afterData & 3))); // Pad to 4-byte alignment
    if (afterData < aligned)
    {
        memset(afterData, 0, (int)aligned - (int)afterData);
    }

    // Total size = offset from destination buffer to end of aligned data
    *outSize = (int)aligned - (int)destBuffer;
}