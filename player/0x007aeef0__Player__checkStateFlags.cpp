// FUNC_NAME: Player::checkStateFlags
// Function at 0x007aeef0: Check if either bit0 or bit3 of the state flags at offset 0x894 is set.
// Returns 1 if either flag is set, 0 otherwise.
int __thiscall Player::checkStateFlags(void) {
    int result = 1;
    // Check bit0 of byte at +0x894 and bit3 of uint at +0x894
    if (((*(byte *)(this + 0x894) & 1) == 0) && ((*(uint *)(this + 0x894) >> 3 & 1) == 0)) {
        result = 0;
    }
    return result;
}