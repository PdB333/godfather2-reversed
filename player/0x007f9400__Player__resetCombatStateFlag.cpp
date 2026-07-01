// FUNC_NAME: Player::resetCombatStateFlag
// Zeros the combat state flag at offset 0x1bfc. Called during player reset.
void __thiscall Player::resetCombatStateFlag() {
    this->m_combatStateFlag = 0; // offset 0x1bfc
}