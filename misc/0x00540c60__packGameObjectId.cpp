// FUNC_NAME: packGameObjectId
unsigned int __cdecl packGameObjectId(unsigned int type, unsigned int subType, unsigned int index)
{
    // Pack three fields into a 32-bit ID:
    // bits 0-4: index (5 bits)
    // bits 5-9: subType (5 bits)
    // bits 16-27: type (12 bits)
    // bits 10-15 and 28-31 unused (reserved)
    return ((type & 0xfff) << 0xb | subType & 0x1f) << 5 | index & 0x1f;
}