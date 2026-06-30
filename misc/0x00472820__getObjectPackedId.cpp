// FUNC_NAME: getObjectPackedId
unsigned int __fastcall getObjectPackedId(void* param_1)
{
    // Read a 4-byte value from the object at offset +0x168 (points to some data block)
    unsigned int* dataBlock = *(unsigned int**)((char*)param_1 + 0x168);
    // Shift the first 4 bytes right by 8 to get a 24-bit value (upper part)
    unsigned int upper = *dataBlock >> 8;
    // Extract a byte at offset +0x62 within the data block (lower 8 bits)
    unsigned char lower = *(unsigned char*)((char*)dataBlock + 0x62);
    // Combine: upper (24 bits) | lower (8 bits) -> 32-bit result
    return (upper & 0xFFFFFF) | ((unsigned int)lower << 24);
}