// FUNC_NAME: Player::isInputBlocked
bool __fastcall Player::isInputBlocked(Player* this)
{
    // Check bit 23 of the gameplay state flag at offset 0x249c (likely pause/cutscene state)
    const bool flag1 = (*(uint32_t*)((uint8_t*)this + 0x249c) >> 0x17) & 1;
    // Check bit 9 of the interruption flag at offset 0x8e0 (likely menu/dialog state)
    const bool flag2 = (*(uint32_t*)((uint8_t*)this + 0x8e0) >> 9) & 1;
    // Input is blocked if either flag is set
    return flag1 || flag2;
}