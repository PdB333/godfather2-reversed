// FUNC_NAME: Player::areCoverFlagsActive

bool __fastcall Player::areCoverFlagsActive(void *thisPtr) {
    // Check two flag bytes at offsets +0x3c5 and +0x3c7
    // Likely indicates player is both in cover and has weapon ready or similar
    return (*(char *)((int)thisPtr + 0x3c7) != '\0') && (*(char *)((int)thisPtr + 0x3c5) != '\0');
}