// FUNC_NAME: Player::setFlagAt0xa30
// Address: 0x007f74e0 - Sets a boolean flag at offset 0xa30 to true (1)
void __thiscall Player::setFlagAt0xa30(Player *this) {
    *(bool *)((char *)this + 0xa30) = true; // +0xa30: flag (likely gameplay-specific)
}