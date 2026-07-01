// Xbox PDB: EARS_Modules_TelemetryListener_LinkMessages
// FUNC_NAME: MultiplayerScenarioManager::registerMultiplayerMessages
void __fastcall MultiplayerScenarioManager::registerMultiplayerMessages(int this)
{
  int *piVar1;
  
  if (DAT_01206940 != 0) {
    FUN_00408900(this, &DAT_01206940, 0x8000);
  }
  piVar1 = (int *)(this + 0x14);
  FUN_00408240(piVar1, "iMsgMultiplayerGameStart");
  if (*piVar1 != 0) {
    FUN_00408900(this, piVar1, 0x8000);
  }
  piVar1 = (int *)(this + 0x1c);
  FUN_00408240(piVar1, "iMsgMultiplayerGameEnd");
  if (*piVar1 != 0) {
    FUN_00408900(this, piVar1, 0x8000);
  }
  piVar1 = (int *)(this + 0x24);
  FUN_00408240(piVar1, "iMsgPlayerDeath");
  if (*piVar1 != 0) {
    FUN_00408900(this, piVar1, 0x8000);
  }
  piVar1 = (int *)(this + 0x2c);
  FUN_00408240(piVar1, "iMsgPostScoreboardUpdate");
  if (*piVar1 != 0) {
    FUN_00408900(this, piVar1, 0x8000);
  }
  piVar1 = (int *)(this + 0x34);
  FUN_00408240(piVar1, "iMsgAptScreenShown");
  if (*piVar1 != 0) {
    FUN_00408900(this, piVar1, 0x8000);
  }
  piVar1 = (int *)(this + 0x3c);
  FUN_00408240(piVar1, "iMsgAptScreenHidden");
  if (*piVar1 != 0) {
    FUN_00408900(this, piVar1, 0x8000);
  }
  piVar1 = (int *)(this + 0x44);
  FUN_00408240(piVar1, "iMsgCityChanged");
  if (*piVar1 != 0) {
    FUN_00408900(this, piVar1, 0x8000);
  }
  *(undefined4 *)(this + 0x94) = 7;  // +0x94: message registration count
  return;
}