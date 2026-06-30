// FUN_NAME: NpcComponent::getStatusInteger
// Function at 0x0068b910: Simple wrapper that retrieves an integer status from the object via internal getter.
// It calls FUN_006039d0 (likely internalGetStatus) with this, pointer to output int, and a dummy byte pointer (unused).
// Returns the integer value obtained.

int NpcComponent::getStatusInteger(void)
{
    int result = 0;
    byte unusedByte; // Not used in this wrapper, possibly for extended info
    // Call internal method at 0x006039d0 to fill result and maybe unusedByte
    FUN_006039d0(this, &result, &unusedByte);
    return result;
}