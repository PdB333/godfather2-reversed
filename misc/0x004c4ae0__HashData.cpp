// FUNC_NAME: HashData
// Address: 0x004c4ae0
// Role: Compute a custom 32-bit hash over a 16-byte buffer (likely a checksum for network packets or game objects).
// This appears to be an inline hash using signed integer arithmetic with carefully chosen coefficients,
// possibly derived from a polynomial or cryptographic constant.
int __fastcall HashData(char* data)
{
    // The hash combines bytes at offsets 0..15 using large 32-bit signed multipliers.
    // Each byte is treated as a signed char (int promotion) before multiplication.
    return data[7] * -0x2ce641ff   + // -752,348,159
           data[6] * -0x4ea93dc1   + // -1,321,203,393
           data[3] * -0x3377e2ff   + // -862,297,343
           data[9] * -0x29d5117f   + // -702,902,143
           data[8] * -0x5cee4e41   + // -1,559,555,137
           data[0xc] * 0x2e86d0bf  + // +782,282,943
           data[1] * 0x50c7ac81    + // +1,352,531,073
           data[10] * 0x162c613f   + // +372,545,343
           data[2] * 0x7280233f    + // +1,919,344,447
           data[5] * 0x6698cd81    + // +1,718,485,377
           data[4] * 0xd1b92bf     + // +219,687,103
           *data * -0x725b8c41     + // -1,917,128,257
           data[0xb] * 0x43ec5f01  + // +1,140,999,425
           data[0xd] * 0x7e0f81    + // +8,257,921
           data[0xe] * 0x1003f     + // +65,599
           (int)data[0xf];           // last byte, no multiplier
}