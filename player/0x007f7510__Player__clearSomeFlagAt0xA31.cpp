// FUNC_NAME: Player::clearSomeFlagAt0xA31
void __thiscall Player::clearSomeFlagAt0xA31(Player* this) {
    // Set the boolean flag at offset 0xA31 to false (0)
    *(byte*)((int)this + 0xa31) = 0;
}