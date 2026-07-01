// FUNC_NAME: TypeDescriptor::compareWith
unsigned int __thiscall TypeDescriptor::compareWith(int* thisPtr, int* otherPtr)
{
    // Assert that both objects have valid (non-zero) and matching type IDs (first 4 bytes)
    if ((*thisPtr == 0) || (*thisPtr != *otherPtr)) {
        assertionFailure(); // FUN_00b97aea – triggers assertion/error
    }
    // Extract 24-bit subtype/version field from the second 4-byte field (+0x04)
    unsigned int high24 = ((unsigned int)(thisPtr[1])) >> 8;
    // Check equality of the entire second field
    bool subTypeEqual = (thisPtr[1] == otherPtr[1]);
    // Combine: high24 forms upper 24 bits, equality flag is low byte
    return (high24 << 8) | (subTypeEqual ? 1 : 0);
}