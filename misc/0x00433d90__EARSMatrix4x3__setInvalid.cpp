// FUNC_NAME: EARSMatrix4x3::setInvalid
// Address: 0x00433d90
// Initializes a 4x3 double matrix structure with an invalid type flag (-1) and zero padding.
// The matrix data is filled using uninitialized stack variables, resulting in undefined values.
// Structure layout:
//   +0x00: int32 type (set to -1)
//   +0x04: double row0_col0
//   +0x0C: double row0_col1
//   +0x14: double row0_col2
//   +0x1C: double row1_col0
//   +0x24: double row1_col1
//   +0x2C: double row1_col2
//   +0x34: double row2_col0
//   +0x3C: double row2_col1
//   +0x44: double row2_col2
//   +0x4C: double row3_col0
//   +0x54: double row3_col1
//   +0x5C: double row3_col2
//   +0x64: uint8 padding (set to 0)

void __thiscall EARSMatrix4x3::setInvalid(void)
{
    uint32_t uStack_1c;      // uninitialized
    uint64_t local_18;       // uninitialized
    uint32_t local_10;       // uninitialized

    // Each row is filled with the same triple of uninitialized values
    *(uint64_t *)((uint32_t *)this + 1) = (uint64_t)uStack_1c << 0x20; // +0x04
    *(uint64_t *)((uint32_t *)this + 3) = local_18;                   // +0x0C
    *(uint64_t *)((uint32_t *)this + 5) = (uint64_t)local_10;        // +0x14

    *(uint64_t *)((uint32_t *)this + 7) = (uint64_t)uStack_1c << 0x20; // +0x1C
    *(uint64_t *)((uint32_t *)this + 9) = local_18;                   // +0x24
    *(uint64_t *)((uint32_t *)this + 0xB) = (uint64_t)local_10;      // +0x2C

    *(uint64_t *)((uint32_t *)this + 0xD) = (uint64_t)uStack_1c << 0x20; // +0x34
    *(uint64_t *)((uint32_t *)this + 0xF) = local_18;                   // +0x3C
    *(uint64_t *)((uint32_t *)this + 0x11) = (uint64_t)local_10;       // +0x44

    *(uint64_t *)((uint32_t *)this + 0x13) = (uint64_t)uStack_1c << 0x20; // +0x4C
    *(uint64_t *)((uint32_t *)this + 0x15) = local_18;                   // +0x54

    // Set type flag to -1 (invalid)
    *(uint32_t *)this = 0xffffffff;

    // Write last double (row3_col2's high part already set, now low part)
    *(uint64_t *)((uint32_t *)this + 0x17) = (uint64_t)local_10;       // +0x5C

    // Zero padding byte
    *(uint8_t *)((uint32_t *)this + 0x19) = 0;                         // +0x64
}