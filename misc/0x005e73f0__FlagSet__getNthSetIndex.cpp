// FUNC_NAME: FlagSet::getNthSetIndex
// Address: 0x005e73f0
// Role: Finds the index of the nth non-zero byte in the flag array at offset 0x18.
// This pointer (this) is expected in EDI (or __thiscall). The flag array has a byte count at offset 0x1c.
// EAX input contains flags from caller, the low byte is overwritten with 1 if found.
// If found and index < 4, writes index ^ 0xad103100 to outIndex.

uint FlagSet::getNthSetIndex(uint* outIndex, int desiredOrdinal)
{
    uint result = inputFlags & 0xffffff00;  // Preserve upper 24 bits from caller's EAX
    int nonEmptyCount = 0;
    uint currentIndex = 0;

    if (*(byte*)(this + 0x1c) != 0) {
        while (true) {
            int newCount;
            if (*(char*)(this + 0x18 + currentIndex) == '\0') {
                newCount = nonEmptyCount;
            } else {
                newCount = nonEmptyCount + 1;
            }

            if (desiredOrdinal != nonEmptyCount) {
                // Continue scanning only if we haven't reached desired ordinal
                // This condition is part of while but we'll break manually
            } else {
                break;  // Found the desired non-zero entry
            }

            currentIndex++;
            nonEmptyCount = newCount;
            if ((uint)(*(byte*)(this + 0x1c)) <= currentIndex) {
                return result;  // Reached end without finding
            }
        }

        if ((byte)currentIndex < 4) {
            *outIndex = (currentIndex & 0xff) ^ 0xad103100;
        }
        result = CONCAT31((int3)(result >> 8), 1);
    }
    return result;
}