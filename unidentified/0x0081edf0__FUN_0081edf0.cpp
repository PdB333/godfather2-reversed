// FUNC_NAME: SomeClass::queueAnimationOrSomething
void __thiscall FUN_0081edf0(int this, undefined4 param_2, char param_3)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int local_44 [4];
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  undefined4 local_28;
  int *local_24;
  undefined1 local_20 [28];
  
  iVar5 = FUN_004262f0(0);
  local_44[1] = 0;
  local_44[2] = 0;
  local_44[3] = DAT_00e44634;
  local_34 = _DAT_00d5780c;
  iVar6 = FUN_0081ddd0(param_2);
  if (iVar6 != 0) {
    local_24 = local_44 + 1;
    local_28 = 0xffffffff;
    local_30 = 5;
    local_2c = iVar5;
    FUN_004eacb0(iVar6);
    piVar7 = (int *)FUN_004df3c0(local_44,local_20,iVar5 + 0x40,0x1ff,0,&local_30);
    piVar1 = (int *)(this + 0xf0);
    if (*(int *)(this + 0xf0) != 0) {
      *(undefined4 *)(*(int *)(this + 0xf0) + 8) = 0;
      *piVar1 = 0;
    }
    iVar5 = *piVar7;
    *piVar1 = iVar5;
    if (iVar5 != 0) {
      *(int **)(iVar5 + 8) = piVar1;
      *piVar7 = 0;
    }
    if (local_44[0] != 0) {
      *(undefined4 *)(local_44[0] + 8) = 0;
    }
    FUN_004df830(*(undefined4 *)(this + 0x104));
    if (param_3 != '\0') {
      iVar5 = *(int *)(this + 0x104);
      uVar2 = *(undefined4 *)(this + 0x84);
      uVar3 = *(undefined4 *)(this + 0x88);
      uVar4 = *(undefined4 *)(this + 0x8c);
      *(undefined4 *)(iVar5 + 0x10) = *(undefined4 *)(this + 0x80);
      *(undefined4 *)(iVar5 + 0x14) = uVar2;
      *(undefined4 *)(iVar5 + 0x18) = uVar3;
      *(undefined4 *)(iVar5 + 0x1c) = uVar4;
      return;
    }
    iVar5 = *(int *)(this + 0x104);
    uVar2 = *(undefined4 *)(this + 0x94);
    uVar3 = *(undefined4 *)(this + 0x98);
    uVar4 = *(undefined4 *)(this + 0x9c);
    *(undefined4 *)(iVar5 + 0x10) = *(undefined4 *)(this + 0x90);
    *(undefined4 *)(iVar5 + 0x14) = uVar2;
    *(undefined4 *)(iVar5 + 0x18) = uVar3;
    *(undefined4 *)(iVar5 + 0x1c) = uVar4;
  }
  return;
}