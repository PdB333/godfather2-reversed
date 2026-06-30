// FUNC_NAME: Matrix4x4::setFrom16Floats
void __fastcall Matrix4x4::setFrom16Floats(float *this, float *src)
{
    // Copy 16 floats from src to this (4x4 matrix)
    // Offsets: +0x30 to +0x6C (16 floats * 4 bytes = 64 bytes)
    this[0x30/4] = src[0];   // +0x30
    this[0x34/4] = src[1];   // +0x34
    this[0x38/4] = src[2];   // +0x38
    this[0x3C/4] = src[3];   // +0x3C
    this[0x40/4] = src[4];   // +0x40
    this[0x44/4] = src[5];   // +0x44
    this[0x48/4] = src[6];   // +0x48
    this[0x4C/4] = src[7];   // +0x4C
    this[0x50/4] = src[8];   // +0x50
    this[0x54/4] = src[9];   // +0x54
    this[0x58/4] = src[10];  // +0x58
    this[0x5C/4] = src[11];  // +0x5C
    this[0x60/4] = src[12];  // +0x60
    this[0x64/4] = src[13];  // +0x64
    this[0x68/4] = src[14];  // +0x68
    this[0x6C/4] = src[15];  // +0x6C
}