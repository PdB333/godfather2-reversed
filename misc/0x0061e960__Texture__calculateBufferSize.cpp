// FUNC_NAME: Texture::calculateBufferSize
// Address: 0x0061e960
// Role: Calculates the memory size required for a texture buffer based on width, height, and an optional extra offset (e.g., for mipmaps).
// The function first checks an initialization flag (+0x23); if zero, it calls initializeSize() (0x0061e810). 
// Size calculation involves alignment to 128-byte boundaries and a constant base offset of 0x478ffc (likely a global texture pool base).
// If param_1 != 0, the third field (offset 8) is added (possibly for mip level data).

class Texture {
public:
    int m_width;          // +0x00
    int m_height;         // +0x04
    int m_extraOffset;    // +0x08 (used when param_1 != 0)
    // ... other members ...
    char m_initialized;   // +0x23 (byte flag)

    // Internal initialization function (0x0061e810)
    bool initializeSize();

    // Main buffer size calculation
    int calculateBufferSize(char param_1);
};

int Texture::calculateBufferSize(char param_1) {
    // If not initialized, try to initialize; fail if can't
    if (m_initialized == 0) {
        if (!initializeSize()) {
            return 0;
        }
    }

    int w = m_width;
    int h = m_height;

    // Compute padded dimensions (with 0x60 extra on each axis)
    uint paddedArea = (w + 0x60) * (h + 0x60);
    uint area = w * h;

    // Align to 128-byte boundaries (0xffffff80 mask)
    int size = ((paddedArea + 0xe0 + (paddedArea >> 2) * 2 + w) & 0xffffff80) +
               (((area >> 2) + 0x80 & 0xffffff80) * 2 + (area + 0x80 & 0xffffff80));
    size = size * 3 + 0x478ffc;  // Base pool offset (likely fixed heap start)

    if (param_1 != 0) {
        size += m_extraOffset;   // Additional data (e.g., mipmap chain)
    }

    return size;
}