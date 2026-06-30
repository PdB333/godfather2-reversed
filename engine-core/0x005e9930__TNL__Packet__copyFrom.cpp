// FUNC_NAME: TNL::Packet::copyFrom
// Function at 0x005e9930 - copies a 144-byte packet structure (36 DWORDs)
// Used by TNL networking layer for packet assignment/replication

struct Packet {
    uint32_t data[36];  // 36 * 4 = 144 bytes
};

void __thiscall Packet::copyFrom(const Packet *source)
{
    // Copy first and last DWORDs
    this->data[0] = source->data[0];        // offset 0x00
    this->data[35] = source->data[35];      // offset 0x8C

    // Unrolled copy of DWORDs 1 through 32 in two 16-DWORD blocks
    uint32_t *dst = &this->data[1];
    const uint32_t *src = &source->data[3];
    int iteration = 2;
    do {
        *dst = *(const uint32_t *)((int)source - (int)this + (int)dst);  // equivalent to src-aligned copy
        dst[1] = src[-1];
        dst[2] = src[0];
        dst[3] = src[1];
        dst[4] = src[2];
        dst[5] = src[3];
        dst[6] = src[4];
        dst[7] = src[5];
        dst[8] = src[6];
        dst[9] = src[7];
        dst[10] = src[8];
        dst[11] = src[9];
        dst[12] = src[10];
        dst[13] = src[11];
        dst[14] = src[12];
        dst[15] = src[13];
        dst += 16;
        src += 16;
        iteration--;
    } while (iteration != 0);

    // Copy remaining DWORDs at offsets 0x84 and 0x88
    this->data[33] = source->data[33];  // offset 0x84
    this->data[34] = source->data[34];  // offset 0x88
}