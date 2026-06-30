// FUNC_NAME: GameTimeManager::update
void GameTimeManager::update(float deltaTime)

{
  if (DAT_00e2fc44 < deltaTime) {
    if (DAT_012055a1 != '\0') {
      FUN_00597070(deltaTime);
    }
    FUN_00596b90(deltaTime);
    return;
  }
  FUN_00596b90(0);
  return;
}