// FUNC_NAME: UnknownClass::convertInternalToExternalFlags
// Function at 0x00724c60 - Converts internal flags (stored at offset +0x120) to an external bitmask.
// Bit mappings:
//   Internal 0x10 -> External 0x20005
//   Internal 0x40 -> External 0x8
//   Internal 0x80 (sign bit when cast to char) -> External 0x200
//   Internal 0x200 -> External 0x1000
//   Internal 0x20 -> External 0x2000002
uint __thiscall UnknownClass::convertInternalToExternalFlags() {
    uint internalFlags = *(uint *)(this + 0x120);
    uint result = 0;

    if ((internalFlags & 0x10) != 0) {
        result = 0x20005;
    }
    if ((internalFlags & 0x40) != 0) {
        result |= 0x8;
    }
    if ((char)internalFlags < 0) {   // checks bit 7 (sign)
        result |= 0x200;
    }
    if ((internalFlags & 0x200) != 0) {
        result |= 0x1000;
    }
    if ((internalFlags & 0x20) != 0) {
        result |= 0x2000002;
    }
    // Note: The decompilation has a duplicate check for 0x200 above; it's likely an artifact.
    return result;
}