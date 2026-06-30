// FUNC_NAME: EARSVariantHandle::assignVariant

void __thiscall EARSVariantHandle::assignVariant(const EARSVariantHandle& source1, const EARSVariantHandle& source2, uint32 extraParam) {
    // +0x00: m_typePtr (pointer to uint8 type byte)
    // +0x04: m_dataPtr (pointer to 32-byte data block)
    uint8 srcType = *source2.m_typePtr;               // Type of source2
    if (*this->m_typePtr != 2) {                       // If this variant is not internal-data type
        if (srcType == 2) {                            // Source2 has internal data
            *this->m_typePtr = 2;                      // Set this type to internal-data
            // Copy 32 bytes of data from source2 to this
            uint32* dest = (uint32*)this->m_dataPtr;
            uint32* src  = (uint32*)source2.m_dataPtr;
            dest[0] = src[0];
            dest[1] = src[1];
            dest[2] = src[2];
            dest[3] = src[3];
            dest[4] = src[4];
            dest[5] = src[5];
            dest[6] = src[6];
            dest[7] = src[7];
        } else {
            *this->m_typePtr = 0;                      // Set type to empty/null (0)
        }
    } else {                                           // This variant is internal-data type
        float* thisData = (float*)this->m_dataPtr;
        *this->m_typePtr = 2;                          // Ensure type is still 2 (redundant)
        if (srcType == 2) {                            // Source2 also has internal data
            // Call helper to combine or transform data (e.g., interpolation)
            FUN_005781f0(thisData, extraParam);        // ThisData + extraParam modification
        } else {
            // Fallback: copy data from source1 into this
            uint32* dest = (uint32*)thisData;
            uint32* src  = (uint32*)source1.m_dataPtr;
            dest[0] = src[0];
            dest[1] = src[1];
            dest[2] = src[2];
            dest[3] = src[3];
            dest[4] = src[4];
            dest[5] = src[5];
            dest[6] = src[6];
            dest[7] = src[7];
        }
    }
}