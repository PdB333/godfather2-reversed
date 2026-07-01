// FUNC_NAME: getCompositeId
// 0x0089c630 - constructs a 32-bit composite ID from global pointer and a tag byte at offset +0xD3
// The global pointer DAT_01129914 is likely a pointer to a singleton (e.g., a manager or root object).
// This function reads the byte at offset 0xD3 of that structure and replaces the low byte of the pointer's value,
// effectively packing a type/version tag into the address to form a unique identifier.

uint32_t getCompositeId()
{
    uint32_t ptrValue = (uint32_t)DAT_01129914;
    uint8_t tagByte = *(uint8_t*)(DAT_01129914 + 0xD3);
    return (ptrValue & 0xFFFFFF00) | tagByte;
}