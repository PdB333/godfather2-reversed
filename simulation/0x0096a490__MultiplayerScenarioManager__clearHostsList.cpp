// FUNC_NAME: MultiplayerScenarioManager::clearHostsList
void MultiplayerScenarioManager::clearHostsList(void)
{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_01129930; // this pointer (MultiplayerScenarioManager instance)
  FUN_005a04a0("ClearHostsList",0,&DAT_00d8cdec,0); // log or notify event "ClearHostsList"
  if (iVar1 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = iVar1 + 0x10; // offset to hosts list container (likely +0x10)
  }
  FUN_005c0260(iVar2,&LAB_00969090,0); // iterate/clear hosts list using callback at LAB_00969090
  *(uint *)(iVar1 + 0x6f4) = *(uint *)(iVar1 + 0x6f4) | 8; // set flag bit 3 at +0x6f4 (e.g., dirty flag)
  return;
}