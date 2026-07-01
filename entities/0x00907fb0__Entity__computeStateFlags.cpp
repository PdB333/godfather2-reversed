// FUNC_NAME: Entity::computeStateFlags
// Address: 0x00907fb0
// Role: Computes a combined flags value based on entity type and input flag.
// Offsets: +0x04 = type (int), +0x1c = baseFlags (uint)

uint Entity::computeStateFlags(uint inputFlag)
{
    uint baseFlags = *(uint *)(this + 0x1c);
    int type = *(int *)(this + 0x04);

    // Always set bit 11 if inputFlag's LSB is set
    uint result = (inputFlag & 1) << 0xb | baseFlags;

    if (type == 1) {
        // Type 1: add bit 7 (0x80)
        return result | 0x80;
    }
    if (type == 4) {
        // Type 4: add bit 8 (0x100)
        return result | 0x100;
    }
    if (type == 5) {
        // Type 5: add bit 9 (0x200)
        result |= 0x200;
    }
    return result;
}