// FUNC_NAME: checkObjectStatusFlag
// Function at 0x00711210: checks a byte flag at offset 0x2c. Returns 1 if bit0 is set and bit7 is clear (signed char >= 0), else 0.
// Likely a member function of an EARS engine class.
int __thiscall checkObjectStatusFlag(void* thisPtr) {
    signed char flags = *(signed char*)((int)thisPtr + 0x2c); // +0x2c: status flags byte
    if ((flags & 1) != 0 && flags >= 0) {
        return 1;
    }
    return 0;
}