// FUNC_NAME: DataBlock::fixupSelfRelativePointers
// Reconstructs self-relative pointers into absolute pointers by adding the object's base address.
// Offsets are relative to the start of this object (this pointer).
// Returns 1 on success.

bool DataBlock::fixupSelfRelativePointers()
{
    int* base = reinterpret_cast<int*>(this);

    // Relocate pointer at offset 0x50: originally a relative offset, now becomes absolute
    int rel50 = *(base + 0x50 / 4);
    *(base + 0x50 / 4) = rel50 + reinterpret_cast<int>(base);
    int current = *(base + 0x50 / 4); // now absolute

    // +0x0c = current + (field at +0x54)
    *(base + 0x0c / 4) = current + *(base + 0x54 / 4);

    // +0x14 = current + (field at +0x10) * 8
    *(base + 0x14 / 4) = current + *(base + 0x10 / 4) * 8;

    // +0x18 = current + (field at +0x3c) * 4
    *(base + 0x18 / 4) = current + *(base + 0x3c / 4) * 4;

    // +0x20 = current + (field at +0x1c)
    *(base + 0x20 / 4) = current + *(base + 0x1c / 4);

    // +0x28 = current + (field at +0x24)
    *(base + 0x28 / 4) = current + *(base + 0x24 / 4);

    // Relocate pointer at offset 0x30, similar to 0x50
    int rel30 = *(base + 0x30 / 4);
    *(base + 0x30 / 4) = rel30 + reinterpret_cast<int>(base);
    current = *(base + 0x30 / 4);

    // +0x34 = current + (field at +0x38) * 0x18
    *(base + 0x34 / 4) = current + *(base + 0x38 / 4) * 0x18;

    return true;
}