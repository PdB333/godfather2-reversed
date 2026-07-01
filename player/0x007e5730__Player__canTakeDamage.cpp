// FUNC_NAME: Player::canTakeDamage
bool __fastcall Player::canTakeDamage(int this)
{
  int gameState;
  uint flags;

  gameState = FUN_007a5f40(); // likely GameManager::getGameState()
  if (gameState != 2) { // 2 = in-game state
    return false;
  }
  flags = *(uint *)(*(int *)(this + 0x58) + 0x8e4); // +0x58 = m_pPlayerData, +0x8e4 = m_damageFlags
  if ((((flags >> 0x1e & 1) != 0) || ((int)flags < 0)) && // check bit 30 (invulnerable) or bit 31 (god mode)
     (gameState = FUN_007e56b0(*(int *)(this + 0x58)), gameState == 0)) { // likely PlayerData::isInCutscene()
    return false;
  }
  return true;
}