// Xbox PDB: EARS_Apt_UIFrontend_ShowPlasmaErrorPopup
// FUNC_NAME: MultiplayerScenarioManager::handleOnlineFailedConnect
void MultiplayerScenarioManager::handleOnlineFailedConnect(void)
{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_01223484;
  iVar2 = 0;
  if (((DAT_01223484 != 0) &&
      (*(int *)(DAT_01223484 + 0x28) != 0 || *(int *)(DAT_01223484 + 0x2c) != 0)) &&
     ((undefined4 *)(DAT_01223484 + 0x28) != (undefined4 *)0x0)) {
    *(undefined4 *)(DAT_01223484 + 0x28) = 0;
    *(undefined4 *)(iVar1 + 0x2c) = 0;
  }
  (**(code **)(*DAT_011305a0 + 0x2c))();
  DAT_00e5672c = 0x11;
  FUN_00566b70();
  iVar1 = FUN_009c8e50(0xf0);
  if (iVar1 != 0) {
    iVar2 = FUN_00982280(0);
  }
  *(undefined4 *)(iVar2 + 0xc) = 2;
  FUN_00981eb0("$mp_online_failed_connect");
  *(undefined4 *)(iVar2 + 0x20) = 0xb9754031;
  *(undefined4 *)(iVar2 + 0x1c) = 0x997dee17;
  *(undefined1 **)(iVar2 + 0x14) = &LAB_00933aa0;
  FUN_00982e10();
  return;
}