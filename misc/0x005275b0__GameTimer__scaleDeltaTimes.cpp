// FUNC_NAME: GameTimer::scaleDeltaTimes
void GameTimer::scaleDeltaTimes(void)

{
  float fVar1;
  
  fVar1 = DAT_00e2b1a4 / DAT_01125220; // timeScale = targetDelta / baseDelta
  _DAT_01125200 = fVar1 * _DAT_01125200; // deltaTime1 scaled
  _DAT_01125204 = fVar1 * _DAT_01125204; // deltaTime2 scaled
  _DAT_01125208 = fVar1 * _DAT_01125208; // deltaTime3 scaled
  _DAT_0112520c = fVar1 * _DAT_0112520c; // deltaTime4 scaled
  return;
}