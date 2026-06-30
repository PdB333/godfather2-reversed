// FUNC_NAME: Entity::applyDesiredOrientation
void __thiscall Entity::applyDesiredOrientation(bool applyRandomYaw)
{
    // Copy target orientation (stored at +0x384..0x39c) to current orientation (at +0x46c..0x484)
    // The orientation data is 28 bytes: three 8-byte chunks and one 4-byte chunk.
    // Likely includes yaw, pitch, roll, and a scale/heading value.
    *(uint64 *)(this + 0x46c) = *(uint64 *)(this + 0x384);
    *(uint64 *)(this + 0x474) = *(uint64 *)(this + 0x38c);
    *(uint64 *)(this + 0x47c) = *(uint64 *)(this + 0x394);
    *(uint32 *)(this + 0x484) = *(uint32 *)(this + 0x39c);

    if (applyRandomYaw) {
        // Generate a random integer and mask off high bits, then overwrite the first
        // 4 bytes of the current yaw field (at +0x46c) with a pseudo-random value.
        uint randomValue = FUN_00b9a1c0();               // likely rand() or GetRandomInt
        *(uint32 *)(this + 0x46c) = randomValue & ((int)randomValue < 0 ? -1 : randomValue);
    }

    // Update flags at +0x2d8: set bits 2 and 3 (0xc) to indicate orientation updated
    *(uint32 *)(this + 0x2d8) |= 0xc;

    // Check if bit 6 (0x40) is set – if so, also set bit 5 (0x20) and return early
    if ((*(uint32 *)(this + 0x2d8) >> 6) & 1) {
        *(uint32 *)(this + 0x2d8) |= 0x20;
        return;
    }

    // Otherwise clear bit 5 (0x20)
    *(uint32 *)(this + 0x2d8) &= ~0x20;
}