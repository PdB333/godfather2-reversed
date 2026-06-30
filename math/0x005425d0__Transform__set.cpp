// FUNC_NAME: Transform::set
void __thiscall Transform::set(uint32_t *this_, uint32_t *src1, uint32_t *src2, uint32_t param4, uint32_t param5, uint32_t param6, uint32_t param7)
{
    // Offset 0x20: byte flag indicating if transform is valid
    *(int8_t *)(this_ + 8) = 0; // +0x20: flag = 0
    this_[9] = 0;                // +0x24: tagged pointer/state = 0
    this_[0xd] = param4;         // +0x34
    this_[0xe] = param5;         // +0x38
    this_[0xf] = param6;         // +0x3c
    this_[0x10] = param7;        // +0x40
    this_[0xc] = 0x3e0;          // +0x30: size or flags (992)

    // Copy first 4 words (16 bytes) from src1 (e.g., rotation quaternion or first column)
    this_[0] = src1[0];
    this_[1] = src1[1];
    this_[2] = src1[2];
    this_[3] = src1[3];

    // Copy next 4 words (16 bytes) from src2 (e.g., translation vector or second column)
    this_[4] = src2[0];
    this_[5] = src2[1];
    this_[6] = src2[2];
    this_[7] = src2[3];

    // Mark as initialized
    *(int8_t *)(this_ + 8) = 1; // +0x20: flag = 1

    // Store a tagged pointer (address of the field at +0x30, shifted right by 2, with high bit set)
    this_[9] = ((uint32_t)(this_ + 0xc) >> 2) | 0x40000000; // +0x24
}