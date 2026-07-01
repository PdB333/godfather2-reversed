// FUNC_NAME: PlayerF2FSM::updateFightState
void __fastcall PlayerF2FSM::updateFightState(int thisPtr)
{
  char cVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puStack_18;
  undefined1 auStack_10 [8];
  undefined4 local_8;
  undefined4 local_4;
  
  local_4 = 0;
  local_8 = 0;
  if (*(int *)(thisPtr + 0x50) == 0) {
    piVar3 = (int *)0x0;
  }
  else {
    piVar3 = (int *)(*(int *)(thisPtr + 0x50) + -0x48);
  }
  puStack_18 = &local_8;
  (**(code **)(*piVar3 + 0x1f8))(*(undefined4 *)(thisPtr + 0x58));
  *(uint *)(thisPtr + 0x70) = *(uint *)(thisPtr + 0x70) & 0xfffff6bf;
  puStack_18 = (undefined4 *)0x0;
  if (*(int *)(thisPtr + 0x50) == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(thisPtr + 0x50) + -0x48;
  }
  if ((_DAT_0112e1b4 & 1) == 0) {
    _DAT_0112e1b4 = _DAT_0112e1b4 | 1;
    DAT_0112e1b0 = (float *)&DAT_00d77000;
  }
  if ((iVar2 == 0) ||
     (iVar2 = FUN_00471610(),
     DAT_0112e1b0[1] * *(float *)(iVar2 + 0x14) + *(float *)(iVar2 + 0x10) * *DAT_0112e1b0 +
     DAT_0112e1b0[2] * *(float *)(iVar2 + 0x18) <= _DAT_00e541f0)) {
    *(uint *)(thisPtr + 0x70) = *(uint *)(thisPtr + 0x70) | 0x800;
  }
  if (*(int *)(thisPtr + 0x50) == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(thisPtr + 0x50) + -0x48;
  }
  cVar1 = FUN_00884ac0(auStack_10,*(undefined4 *)(thisPtr + 0x58),iVar2);
  if (cVar1 == '\\0') {
    puStack_18 = *(undefined4 **)(thisPtr + 0x5c);
  }
  else {
    if (*(int *)(thisPtr + 0x50) == 0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)(*(int *)(thisPtr + 0x50) + -0x48);
    }
    (**(code **)(*piVar3 + 0x1d8))(auStack_10,auStack_10);
    if (*(int *)(thisPtr + 0x50) == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(thisPtr + 0x50) + -0x48;
    }
    cVar1 = FUN_00884ac0(auStack_10,*(undefined4 *)(thisPtr + 0x58),iVar2);
    if (cVar1 == '\\0') {
      *(uint *)(thisPtr + 0x70) = *(uint *)(thisPtr + 0x70) | 0x80;
      puStack_18 = *(undefined4 **)(thisPtr + 100);
    }
    else {
      *(uint *)(thisPtr + 0x70) = *(uint *)(thisPtr + 0x70) | 0x100;
    }
  }
  if ((*(uint *)(thisPtr + 0x70) >> 8 & 1) == 0) {
    cVar1 = FUN_008754b0(&puStack_18);
    if (cVar1 != '\\0') {
      *(uint *)(thisPtr + 0x70) = *(uint *)(thisPtr + 0x70) | 0x40;
    }
    iVar2 = FUN_00885a90(&puStack_18);
    if (iVar2 == 0) {
      *(uint *)(thisPtr + 0x70) = *(uint *)(thisPtr + 0x70) & 0xfffffdff;
      return;
    }
    *(uint *)(thisPtr + 0x70) = *(uint *)(thisPtr + 0x70) | 0x200;
    iVar2 = FUN_0043b870(DAT_01131038);
    if ((iVar2 != 0) && (cVar1 = FUN_009afde0(), cVar1 != '\\0')) {
      if (*(int *)(thisPtr + 0x50) == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(thisPtr + 0x50) + -0x48;
      }
      FUN_009b0820(iVar2,DAT_00d5ef88,1);
    }
  }
  return;
}