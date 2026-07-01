//FUNC_NAME: DataBlock::copyFrom
void __thiscall DataBlock::copyFrom(uint32_t *this, const uint32_t *source)
{
    // Copy 17 dwords (68 bytes) from source to this
    this[0] = source[0];
    this[1] = source[1];
    this[2] = source[2];
    this[3] = source[3];
    this[4] = source[4];
    this[5] = source[5];
    this[6] = source[6];
    this[7] = source[7];
    this[8] = source[8];
    this[9] = source[9];
    this[10] = source[10];
    this[11] = source[11];
    this[12] = source[12];
    this[13] = source[13];
    this[14] = source[14];
    this[15] = source[15];
    this[16] = source[16];
}