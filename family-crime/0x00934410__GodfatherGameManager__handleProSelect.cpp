// FUNC_NAME: GodfatherGameManager::handleProSelect
bool GodfatherGameManager::handleProSelect(char param_1)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  undefined2 *puVar5;
  undefined1 *puVar6;
  int iVar7;
  uint uVar8;
  uint local_24;
  undefined1 *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  code *local_14;
  undefined2 *local_10 [3];
  code *local_4;
  
  if (param_1 != '\0') {
    uVar3 = FUN_00699c00();
    cVar2 = FUN_009341d0(uVar3);
    return cVar2 == '\0';
  }
  param_1 = '\0';
  uVar3 = FUN_00697ed0(&param_1);
  cVar2 = FUN_009341d0(uVar3);
  if (cVar2 != '\0') {
    if (param_1 != '\0') {
      return false;
    }
    iVar4 = FUN_009c8e50(0xf0);
    if (iVar4 == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = FUN_00982280(0);
    }
    *(undefined4 *)(iVar4 + 0xc) = 0xe;
    FUN_00981ec0("$ui_pro_select");
    FUN_00981eb0("$ui_pro_select");
    *(undefined1 **)(iVar4 + 0x14) = &LAB_009330e0;
    uVar3 = FUN_0069a880();
    cVar2 = FUN_009341d0(uVar3);
    if (cVar2 == '\0') {
      FUN_009823b0();
      FUN_009c8eb0(iVar4);
      return true;
    }
    uVar8 = (uint)*(ushort *)(DAT_0113056c + 4);
    if ((uVar8 == 0) || (DAT_00e56734 != '\0')) {
      local_24 = 1;
    }
    else {
      local_24 = 0;
    }
    FUN_00982400(local_24);
    if (uVar8 < 6) {
      *(undefined1 *)(iVar4 + 0xec) = 1;
    }
    if (uVar8 != 0) {
      iVar7 = 0;
      local_24 = uVar8;
      do {
        iVar1 = DAT_0113055c + iVar7;
        uVar3 = FUN_004dbef0(iVar1);
        FUN_004dba00(iVar1,uVar3);
        FUN_006047a0(local_10);
        local_20 = (undefined1 *)0x0;
        local_1c = 0;
        local_18 = 0;
        local_14 = (code *)0x0;
        puVar5 = local_10[0];
        if (local_10[0] == (undefined2 *)0x0) {
          puVar5 = &DAT_00e2df14;
        }
        FUN_004ddaf0(puVar5,&local_20);
        puVar6 = local_20;
        if (local_20 == (undefined1 *)0x0) {
          puVar6 = &DAT_0120546e;
        }
        FUN_00981e70(puVar6,0,0);
        if (local_20 != (undefined1 *)0x0) {
          (*local_14)(local_20);
        }
        if (local_10[0] != (undefined2 *)0x0) {
          (*local_4)(local_10[0]);
        }
        iVar7 = iVar7 + 0x504;
        local_24 = local_24 - 1;
      } while (local_24 != 0);
      *(undefined1 *)(iVar4 + 0xed) = 1;
    }
    FUN_00982e10();
  }
  return true;
}