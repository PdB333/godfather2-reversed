// FUNC_NAME: PlayerSM::updateCurrentState
void __thiscall PlayerSM::updateCurrentState(int this, int param_2)

{
  uint uVar1;
  code *pcVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = FUN_006b0ee0(*(undefined4 *)(*(int *)(this + 100) + *(int *)(this + 0x80) * 4));
  FUN_005c1ad0();
  uVar1 = *(uint *)(this + 0xa0);
  if ((uVar1 != 0xffffffff) && (uVar1 < *(uint *)(this + 0x68))) {
    iVar5 = FUN_006b0ee0(*(undefined4 *)(*(int *)(this + 100) + uVar1 * 4));
    if (iVar5 != 0) {
      FUN_0097b440(*(undefined4 *)(iVar5 + 0x48),iVar5 + 0x10,0,DAT_00d5e288);
    }
  }
  piVar3 = DAT_0112fee4;
  iVar5 = *DAT_0112fee4;
  DAT_0112fee4[0x19] = param_2;
  pcVar2 = *(code **)(iVar5 + 0x6c);
  piVar3[0x4d] = iVar4;
  (*pcVar2)();
  (**(code **)(*piVar3 + 0x28))();
  return;
}