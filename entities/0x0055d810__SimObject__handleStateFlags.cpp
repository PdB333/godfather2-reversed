// FUNC_NAME: SimObject::handleStateFlags
void SimObject::handleStateFlags()
{
    // Force set bit 2 (0x4) - possibly indicates "active" or "enabled" flag at +0x110
    *(uint32_t *)(this + 0x110) |= 4;

    // Check if bit 3 (0x8) is set - possibly "pending transition" or "update required" flag
    if ((*(uint32_t *)(this + 0x110) >> 3) & 1)
    {
        // If bit 3 is set, set bit 4 (0x10) - final state flag
        // Then clear bit 3 (remove pending flag)
        *(uint32_t *)(this + 0x110) |= 0x10;
        *(uint32_t *)(this + 0x110) &= 0xfffffff7; // clear bit 3
    }
    else
    {
        // Otherwise, clear both bit 4 and bit 3
        *(uint32_t *)(this + 0x110) &= 0xffffffef; // clear bit 4
        *(uint32_t *)(this + 0x110) &= 0xfffffff7; // clear bit 3
    }

    // Reset timer/counter at +0xD4 to 0 (e.g., elapsed time in state)
    *(uint32_t *)(this + 0xD4) = 0;
}