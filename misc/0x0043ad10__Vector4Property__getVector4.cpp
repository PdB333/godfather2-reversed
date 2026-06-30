// FUNC_NAME: Vector4Property::getVector4
// Address: 0x0043ad10
// Retrieves a 4-element vector (16 bytes) from this property.
// If m_type != 0x25E3, the data is stored inline at offset +0x08.
// If m_type == 0x25E3, the data is pointed to by m_dataBlockBase + m_dataOffset.
// If m_dataOffset is zero, the output is zeroed.

struct Vector4Property {
    int m_dataOffset;        // +0x00
    short m_padding;         // +0x04
    short m_type;            // +0x06  0x25E3 indicates indirect storage
    union {
        int m_inlineData[4]; // +0x08 (used when m_type != 0x25E3)
        int m_dataBlockBase; // +0x08 (base address of external data, used when m_type == 0x25E3)
    };
};

// __thiscall - param_1 is 'this'
void __thiscall Vector4Property::getVector4(int* outVec4) {
    if (m_type != 0x25E3) {
        // Direct copy from inline storage
        outVec4[0] = m_inlineData[0];
        outVec4[1] = m_inlineData[1];
        outVec4[2] = m_inlineData[2];
        outVec4[3] = m_inlineData[3];
    } else {
        if (m_dataOffset != 0) {
            // Indirect data: base + offset points to a 4-int block
            int* src = (int*)(m_dataBlockBase + m_dataOffset);
            outVec4[0] = src[0];
            outVec4[1] = src[1];
            outVec4[2] = src[2];
            outVec4[3] = src[3];
        } else {
            // No data: zero output
            outVec4[0] = 0;
            outVec4[1] = 0;
            outVec4[2] = 0;
            outVec4[3] = 0;
        }
    }
}