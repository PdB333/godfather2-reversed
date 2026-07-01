// FUNC_NAME: GameStateManager::updateState
void __fastcall GameStateManager::updateState(int this)
{
  char cVar1;
  code *pcVar2;
  
  if (DAT_01130548 != DAT_00e5672c) {
    return;
  }
  if (DAT_01130548 == 6) {
    FUN_00931130(); // likely initializeGameplay
    *(undefined4 *)(this + 0x60) = 0; // +0x60: some flag
    if ((DAT_01130590 & 1) != 0) {
      return;
    }
    FUN_005c0d50(this + 0x14, &LAB_00931e00, 0); // +0x14: callback list
    DAT_01130590 = DAT_01130590 | 1;
    return;
  }
  if (DAT_01130548 == 0x12) {
    pcVar2 = *(code **)(*DAT_0113059c + 0x2c); // vtable call
  }
  else {
    if (DAT_01130548 == 0x13) {
      (**(code **)(*DAT_0113006c + 0x2c))(); // vtable call
      cVar1 = FUN_009c7920(); // likely isSaveGameReady
      if (cVar1 != '\0') {
        (**(code **)(*DAT_01129924 + 4))(); // vtable call
      }
      FUN_005c1b40(); // likely finalizeSaveGame
      goto LAB_00936844;
    }
    if (DAT_01130548 != 0x14) {
      if (DAT_01130548 != 0x11) {
        return;
      }
      *(undefined4 *)(this + 0x6c) = 1; // +0x6c: some flag
      FUN_005a04a0("ForceHighlight", 0, &DAT_00d8963c, 0); // likely setHighlight
      FUN_00935f90(); // likely updateHighlight
      return;
    }
    cVar1 = FUN_009c7920(); // likely isSaveGameReady
    if (cVar1 == '\0') goto LAB_00936844;
    pcVar2 = *(code **)(*DAT_01129924 + 4); // vtable call
  }
  (*pcVar2)();
LAB_00936844:
  DAT_00e5672c = 0x11; // set next state to 0x11
  FUN_00931f80(0); // likely resetStateTimer
  return;
}