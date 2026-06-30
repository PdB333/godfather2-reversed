// FUNC_NAME: Player::setActionCommand
void __thiscall Player::setActionCommand(Player* this, uint32_t command) {
    // this+0x18: pointer to SimNpc (player's simulated NPC component)
    // SimNpc+0x18: field storing the current action command
    *(uint32_t*)(*(int32_t*)((uint8_t*)this + 0x18) + 0x18) = command;
}