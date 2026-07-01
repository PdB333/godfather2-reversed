// FUNC_NAME: GodfatherGameManager::processDialogTreeResult
void GodfatherGameManager::processDialogTreeResult(undefined4 *param_1, undefined4 *param_2, undefined4 *param_3)
{
  char cVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  undefined1 *local_50;
  undefined4 local_4c;
  undefined4 local_48;
  code *local_44;
  undefined1 *local_40;
  undefined4 local_3c;
  undefined4 local_38;
  code *local_34;
  undefined1 *local_30;
  undefined4 local_2c;
  undefined4 local_28;
  code *local_24;
  int local_20 [3];
  code *local_14;
  int local_10 [3];
  code *local_4;
  
  local_30 = (undefined1 *)0x0;
  local_2c = 0;
  local_28 = 0;
  local_24 = (code *)0x0;
  local_20[0] = 0;
  local_20[1] = 0;
  local_20[2] = 0;
  local_14 = (code *)0x0;
  local_50 = (undefined1 *)0x0;
  local_4c = 0;
  local_48 = 0;
  local_44 = (code *)0x0;
  local_40 = (undefined1 *)0x0;
  local_3c = 0;
  local_38 = 0;
  local_34 = (code *)0x0;
  cVar1 = FUN_004d5210(&DAT_00d8107c,&local_30,&local_50);
  if (cVar1 == '\\0') {
    uVar3 = FUN_008f2c90();
    *param_2 = uVar3;
    puVar2 = (undefined1 *)*param_1;
    uVar3 = param_1[1];
    if ((undefined1 *)*param_1 == (undefined1 *)0x0) {
      puVar2 = &DAT_0120546e;
    }
  }
  else {
    puVar2 = local_30;
    if (local_30 == (undefined1 *)0x0) {
      puVar2 = &DAT_0120546e;
    }
    FUN_004dba80(puVar2,local_2c);
    uVar3 = FUN_008f4bf0(local_10);
    *param_2 = uVar3;
    if (local_10[0] != 0) {
      (*local_4)(local_10[0]);
    }
    cVar1 = FUN_004d5210(&DAT_00d8107c,local_20,&local_40);
    if (cVar1 != '\\0') {
      puVar2 = local_40;
      if (local_40 == (undefined1 *)0x0) {
        puVar2 = &DAT_0120546e;
      }
      FUN_004dba80(puVar2,local_3c);
      goto LAB_008f5629;
    }
    puVar2 = local_50;
    uVar3 = local_4c;
    if (local_50 == (undefined1 *)0x0) {
      puVar2 = &DAT_0120546e;
    }
  }
  FUN_004dba80(puVar2,uVar3);
LAB_008f5629:
  uVar3 = FUN_008f4c30(local_10);
  *param_3 = uVar3;
  if (local_10[0] != 0) {
    (*local_4)(local_10[0]);
  }
  if (local_40 != (undefined1 *)0x0) {
    (*local_34)(local_40);
  }
  if (local_50 != (undefined1 *)0x0) {
    (*local_44)(local_50);
  }
  if (local_20[0] != 0) {
    (*local_14)(local_20[0]);
  }
  if (local_30 != (undefined1 *)0x0) {
    (*local_24)(local_30);
  }
  return;
}