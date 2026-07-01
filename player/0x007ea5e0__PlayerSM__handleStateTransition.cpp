// FUNC_NAME: PlayerSM::handleStateTransition
void PlayerSM::handleStateTransition(char param_1, int *param_2, int *param_3)
{
  char cVar1;
  char cVar2;
  char cVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int *unaff_retaddr;
  
  if ((param_1 != '\0') &&
     ((cVar1 = FUN_00481660(), cVar1 != '\0' || (cVar1 = FUN_00481640(), cVar1 != '\0')))) {
    (**(code **)(*param_3 + 0x234))(1,1);
    (**(code **)(*unaff_retaddr + 0x2c))(0x82cdc9c,1,1,0,0x3f800000,0x3f800000);
    return;
  }
  if (param_3 == (int *)0x0) {
    piVar4 = (int *)0x0;
  }
  else {
    piVar4 = (int *)FUN_0043b870(DAT_01131018);
  }
  iVar5 = (**(code **)(*piVar4 + 0x34))();
  cVar2 = FUN_007e9b00(param_3,iVar5);
  cVar1 = (char)param_3[0x6e3];
  *(undefined1 *)(param_3 + 0x782) = 0;
  iVar7 = *(int *)(iVar5 + 0x30);
  if (iVar7 == 3) {
    iVar5 = iVar5 + 0x14;
LAB_007ea986:
    FUN_0046ffe0(iVar5,0);
    (**(code **)(*param_2 + 0x2c))(0x81cfd529,1,1,0,0x3f800000,0x3f800000);
    return;
  }
  if (iVar7 == 4) {
    iVar5 = iVar5 + 0x20;
    goto LAB_007ea986;
  }
  if (((iVar7 == 6) || (uVar6 = FUN_0084d420(iVar7), (uVar6 & 8) != 0)) ||
     (uVar6 = FUN_0084d420(*(undefined4 *)(iVar5 + 0x30)), (uVar6 & 0x40) != 0)) {
    if (cVar1 == '\0') {
      (**(code **)(*param_2 + 0x2c))(0x1b7c7d5b,1,1,0,0x3f800000,0x3f800000);
      return;
    }
    if ((cVar1 != '\x01') && (cVar1 != '\x04')) {
      if (cVar1 != '\x02') {
        return;
      }
      (**(code **)(*param_2 + 0x2c))(0x6d4224e5,1,1,0,0x3f800000,0x3f800000);
      return;
    }
    (**(code **)(*param_2 + 0x2c))(0xbe825b34,1,1,0,0x3f800000,0x3f800000);
    return;
  }
  if ((*(int *)(iVar5 + 0x30) == 9) || (cVar3 = FUN_0084d420(*(int *)(iVar5 + 0x30)), cVar3 < '\0'))
  {
    (**(code **)(*param_2 + 0x2c))(0x576992f2,1,1,0,0x3f800000,0x3f800000);
    *(undefined1 *)(param_3 + 0x782) = 0;
    return;
  }
  if ((*(int *)(iVar5 + 0x30) != 2) && (*(int *)(iVar5 + 0x30) != 1)) {
    return;
  }
  if (cVar1 != '\0') {
    if (cVar1 == '\x01') {
      if ((cVar2 != '\0') && (param_1 == '\0')) {
        (**(code **)(*param_2 + 0x2c))(0x5ce84645,1,1,0,0x3f800000,0x3f800000);
        *(undefined1 *)(param_3 + 0x782) = 1;
        return;
      }
    }
    else {
      if (cVar1 == '\x02') {
        (**(code **)(*param_2 + 0x2c))(0x854f637a,1,1,0,0x3f800000,0x3f800000);
        return;
      }
      if (cVar1 == '\x03') {
        (**(code **)(*param_2 + 0x2c))(0x95c6297a,1,1,0,0x3f800000,0x3f800000);
        return;
      }
      if (cVar1 != '\x04') {
        return;
      }
    }
    (**(code **)(*param_2 + 0x2c))(0x5bf4d367,1,1,0,0x3f800000,0x3f800000);
    return;
  }
  if (cVar2 == '\0') {
    (**(code **)(*param_2 + 0x2c))(0x412eb0db,1,1,0,0x3f800000,0x3f800000);
    return;
  }
  if ((*(int *)(iVar5 + 0xc) == 0) || (*(int *)(iVar5 + 0xc) == 0x48)) {
    iVar7 = 0;
  }
  else {
    if (*(int *)(iVar5 + 0xc) == 0) {
      iVar7 = 0;
    }
    else {
      iVar7 = *(int *)(iVar5 + 0xc) + -0x48;
    }
    iVar7 = FUN_006b1c70(iVar7,0x55859efa);
    if (iVar7 != 0) {
      iVar8 = FUN_00800a90();
      goto LAB_007ea73a;
    }
  }
  iVar8 = 0;
LAB_007ea73a:
  if ((((((*(int *)(iVar5 + 0x30) != 2) || (iVar7 == 0)) || (iVar8 == 0)) ||
       (((*(uint *)(iVar7 + 0x8e0) >> 10 & 1) == 0 || (cVar1 = FUN_00701010(), cVar1 != '\0')))) ||
      (*(char *)(iVar8 + 0x1aa) != '\x02')) && (param_1 == '\0')) {
    (**(code **)(*param_2 + 0x2c))(0x92883cc1,1,1,0,0x3f800000,0x3f800000);
    *(undefined1 *)(param_3 + 0x782) = 1;
    return;
  }
  (**(code **)(*param_2 + 0x2c))(0xc996f012,1,1,0,0x3f800000,0x3f800000);
  return;
}