// FUNC_NAME: EARS::Framework::Object::findOrCreateOrSomething
undefined4 FUN_00814120(int param_1)

{
  uint *puVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  char cVar7;
  undefined4 uVar8;
  uint uVar9;
  undefined **local_90 [18];
  undefined1 local_48 [72];
  
  iVar6 = DAT_0122337c;
  bVar5 = false;
  if ((param_1 == 0) || (param_1 == -0x1e98fd1)) {
    return 0;
  }
  bVar4 = true;
  FUN_00405e80(local_90,param_1,1);
  bVar3 = true;
  do {
    if (bVar4) {
      bVar5 = true;
      uVar8 = FUN_00405f20(local_48);
      cVar7 = FUN_00405f90(uVar8);
      if (cVar7 == '\0') goto LAB_0081419a;
      bVar2 = true;
    }
    else {
LAB_0081419a:
      bVar2 = false;
    }
    if (bVar5) {
      bVar5 = false;
    }
    if (!bVar2) {
      local_90[0] = &PTR_DAT_00e2f0c4;
      if (!bVar4) {
        return 0;
      }
      uVar8 = FUN_00404280(param_1,0,0);
      return uVar8;
    }
    uVar9 = FUN_00405f40();
    for (puVar1 = *(uint **)(*(int *)(iVar6 + 0x50) + (uVar9 % *(uint *)(iVar6 + 0x54)) * 4);
        puVar1 != (uint *)0x0; puVar1 = (uint *)puVar1[2]) {
      if (*puVar1 == uVar9) {
        if ((puVar1 != (uint *)0x0) && (puVar1[1] != 0)) {
          uVar8 = *(undefined4 *)(puVar1[1] + 0x24);
          goto LAB_008141d4;
        }
        break;
      }
    }
    uVar8 = 0xffffffff;
LAB_008141d4:
    switch(uVar8) {
    case 0:
    case 1:
    case 3:
      if (bVar3) goto LAB_00814204;
      break;
    case 0xffffffff:
    case 2:
    case 4:
    case 5:
      if (!bVar3) {
LAB_00814204:
        bVar4 = false;
      }
    }
    (*(code *)local_90[0][1])();
    bVar3 = false;
  } while( true );
}