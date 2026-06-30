// FUNC_NAME: EntityState::updateTransitionFlags
void __fastcall EntityState::updateTransitionFlags(EntityState* thisPtr)
{
    // stateFlags at +0xdc holds a set of bit flags
    uint32_t flags = thisPtr->stateFlags;

    // Check if bit 1 is set
    if ((flags >> 1) & 1) {
        // Clear bit 1, set bits 2, 11, 19 (0x80804 = (1<<2) | (1<<11) | (1<<19))
        thisPtr->stateFlags = (flags & 0xFFFFFFFD) | 0x80804;
        return;
    }

    // Check if bit 2 is set
    if ((flags >> 2) & 1) {
        // Clear bit 2, set bits 1, 11, 19 (0x80802 = (1<<1) | (1<<11) | (1<<19))
        thisPtr->stateFlags = (flags & 0xFFFFFFFB) | 0x80802;
    }
}