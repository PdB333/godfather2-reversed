// FUNC_NAME: ObjectTypeAndHashCompare
uint32_t __thiscall compareTypeAndHash(void* this, void* other)
{
    // Check type field at offset 0x00: must be non-zero and equal
    int* thisFields = (int*)this;
    int* otherFields = (int*)other;
    if ((thisFields[0] == 0) || (thisFields[0] != otherFields[0])) {
        FUN_00b97aea();  // assertion failure or error handler
    }
    // Return combined result:
    // Low 24 bits: upper 24 bits of second field (offset 0x04)
    // High 8 bits: equality flag for second field (1 if equal, 0 otherwise)
    uint32_t upper24 = (uint32_t)(thisFields[1] >> 8) & 0xFFFFFF;
    uint32_t eqFlag = (thisFields[1] == otherFields[1]) ? 1 : 0;
    return (eqFlag << 24) | upper24;
}