// FUNC_NAME: DialogTreeManager::processDialogNode
undefined4 DialogTreeManager::processDialogNode(uint dialogId)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  undefined1 local_50 [32];
  undefined4 local_30;
  undefined4 local_10;
  undefined4 local_c;
  
  if (dialogId < 0x1000) {
    pcVar3 = &DAT_011a0f28 + dialogId * 0x38;
  }
  else {
    pcVar3 = (char *)0x0;
  }
  if ((*pcVar3 != '\x02') && (*pcVar3 != '\x03')) {
    return 0;
  }
  iVar2 = 0;
  if (pcVar3[1] != '\0') {
    do {
      iVar1 = FUN_00606fd0(dialogId,6,iVar2,local_50);
      if (iVar1 == 0) {
        return 0;
      }
      FUN_00614f30(local_c,local_10,local_30);
      FUN_006071a0(local_50);
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)(uint)(byte)pcVar3[1]);
  }
  return 1;
}