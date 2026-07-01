// FUNC_NAME: Entity::testFlagsMasked
bool __thiscall Entity::testFlagsMasked(uint requestedFlags)
{
    // Mask input to only allow valid flag bits (bits 0,1,2,3,5,12,14)
    uint maskedFlags = requestedFlags & 0xffff502f;
    if (maskedFlags != 0 && (*(uint*)(this + 4) & maskedFlags) == maskedFlags) {
        // All requested valid flags are set in the object's state flags at +0x04
        return true;
    }
    return false;
}