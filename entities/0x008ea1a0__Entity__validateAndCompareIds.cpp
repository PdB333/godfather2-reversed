// FUNC_NAME: Entity::validateAndCompareIds
// Function address: 0x008ea1a0
// Role: Validates that two entities have the same non-null type ID, then returns a packed value:
//   high 24 bits = entity instance ID (bits 8-31), low 8 bits = 1 if instance IDs match else 0.
// Called when comparing entity handles or references.
unsigned int __thiscall Entity::validateAndCompareIds(int* thisPtr, int* otherPtr)
{
    // Check that both have non-null type IDs and they are equal
    if ((*thisPtr == 0) || (*thisPtr != *otherPtr)) {
        // Assertion failed: type IDs must be non-zero and matching
        assertionError();
    }

    // Return combined value: instance ID high bits + equality flag in low byte
    int instanceIdThis = thisPtr[1];          // +0x04: instance ID
    int instanceIdOther = otherPtr[1];        // +0x04: instance ID
    unsigned int result = (instanceIdThis & 0xFFFFFF00) | (unsigned int)(instanceIdThis == instanceIdOther);
    return result;
}