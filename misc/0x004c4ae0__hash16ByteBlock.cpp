// FUNC_NAME: hash16ByteBlock
// Function address: 0x004c4ae0
// Role: Custom hash function for 16-byte blocks (likely used for string hashing or data integrity)
// Uses a linear combination of each byte with specific constants (polynomial hash)
int __fastcall hash16ByteBlock(const char* data)
{
    return data[7] * -0x2ce641ff + data[6] * -0x4ea93dc1 + data[3] * -0x3377e2ff +
           data[9] * -0x29d5117f + data[8] * -0x5cee4e41 + data[0xc] * 0x2e86d0bf +
           data[1] * 0x50c7ac81 + data[10] * 0x162c613f + data[2] * 0x7280233f +
           data[5] * 0x6698cd81 + data[4] * 0xd1b92bf + data[0] * -0x725b8c41 +
           data[0xb] * 0x43ec5f01 + data[0xd] * 0x7e0f81 + data[0xe] * 0x1003f +
           (int)data[0xf];
}