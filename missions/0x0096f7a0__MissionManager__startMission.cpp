// FUNC_NAME: MissionManager::startMission
void MissionManager::startMission(int param_1, char param_2)
{
  int iVar1;
  
  iVar1 = FUN_009c8e50(0xf0);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_00982280(0);
  }
  FUN_00981f10(2,3);
  FUN_00981eb0(param_1);
  if (param_2 == '\0') {
    *(undefined4 *)(iVar1 + 0xc) = 0xd;
    FUN_00982400(1);
  }
  else {
    *(undefined4 *)(iVar1 + 0xc) = 0xc;
  }
  *(undefined4 *)(iVar1 + 0x20) = 0xe8d242ca;
  *(undefined1 **)(iVar1 + 0x14) = &LAB_0096f710;
  FUN_00982e10();
  return;
}