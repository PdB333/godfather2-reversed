//FUNC_NAME: Player::getHealth
int __fastcall Player::getHealth(Player* this) {
    // Dereference pointer at +0x360 (likely m_pPlayerData) then read int at +0x10c (health)
    return *(int*)(*(int*)((char*)this + 0x360) + 0x10c);
}