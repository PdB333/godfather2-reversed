// FUNC_NAME: ControllerManager::handleControllerReconnectEvent
uint __thiscall ControllerManager::handleControllerReconnectEvent(int thisPtr, undefined4 param_2)
{
  int iVar1;
  char cVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  undefined1 *puVar7;
  undefined1 *local_10 [3];
  code *local_4;
  
  if (*(char *)(thisPtr + 0x14) == '\x13') {
    uVar3 = FUN_00603330(0x10f05301,param_2);
    return uVar3 & 0xffffff00;
  }
  cVar2 = FUN_0040edb0();
  if (cVar2 == '\0') {
    iVar1 = *(int *)(DAT_0112980c + 4);
    uVar4 = FUN_00683280("GameMainLoop");
    iVar5 = FUN_006833d0(uVar4);
    if (iVar1 == iVar5) {
      cVar2 = FUN_008a4380();
      pcVar6 = "controller_reconnect_specific_paused";
      if (cVar2 == '\0') goto LAB_0068ccaf;
    }
  }
  pcVar6 = "controller_reconnect_specific";
LAB_0068ccaf:
  FUN_004d4a60(local_10,1,"{n:%d}{$%s}",*(byte *)(thisPtr + 0x14) + 1,pcVar6);
  puVar7 = local_10[0];
  if (local_10[0] == (undefined1 *)0x0) {
    puVar7 = &DAT_0120546e;
  }
  FUN_00603970(param_2,puVar7);
  if (local_10[0] != (undefined1 *)0x0) {
    local_10[0] = (undefined1 *)(*local_4)(local_10[0]);
  }
  return (uint)local_10[0] & 0xffffff00;
}