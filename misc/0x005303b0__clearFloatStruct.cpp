// FUNC_NAME: clearFloatStruct
void __thiscall clearFloatStruct(float *this) {
    // Zero out float fields at specific offsets (probably part of a larger struct)
    this[0] = 0.0f;   // +0x00
    this[1] = 0.0f;   // +0x04
    this[2] = 0.0f;   // +0x08
    this[3] = 0.0f;   // +0x0C
    this[4] = 0.0f;   // +0x10
    this[5] = 0.0f;   // +0x14
    this[8] = 0.0f;   // +0x20
    // Fields at indices 6 and 7 (+0x18 and +0x1C) are left unchanged
}