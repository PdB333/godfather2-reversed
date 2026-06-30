// FUNC_NAME: FlagModifier::applyToTarget
void __thiscall FlagModifier::applyToTarget(uint32_t *outModifier, uint32_t *targetFlags, uint32_t globalMask)
{
    // Load the three modifier fields from the object:
    // +0x00: flagsToSet (low 32 bits)
    // +0x04: flagsToClear (high 32 bits)
    // +0x08: qualifier (low byte used as conditional mask trigger)
    uint32_t qualifier = *(uint32_t *)(this + 2); // offset 8 bytes from start (since 'this' is uint64*)

    // Copy the full 64-bit flag pair into outModifier[0..1]
    *(uint64_t *)outModifier = *(uint64_t *)this;
    outModifier[2] = qualifier;

    // If the low byte of qualifier is zero, apply globalMask to both set and clear bits
    if ((char)qualifier == 0)
    {
        outModifier[0] &= globalMask;  // flagsToSet
        outModifier[1] &= globalMask;  // flagsToClear
    }

    // Combine target flags: set bits from outModifier[0], clear bits from outModifier[1]
    *targetFlags = (outModifier[0] | *targetFlags) & ~outModifier[1];
}