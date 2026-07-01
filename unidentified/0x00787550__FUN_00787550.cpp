// FUNC_NAME: SomeClass::addPendingActionOrSomething
void __thiscall FUN_00787550(int this, int param_2)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar1 = FUN_00786720(param_2 + 0xc);
  if (iVar1 == 0) {
    if (*(int *)(this + 0x1a3c) == 0x40) {
      FUN_00786850();
    }
    local_c = 0;
    local_8 = 0;
    local_4 = 0;
    iVar1 = (*(code *)**(undefined4 **)(this + 0x1914))(100,&local_c);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = FUN_007886a0();
    }
    if (*(uint *)(this + 0x1a3c) < 0x40) {
      *(undefined4 *)(this + 0x193c + *(uint *)(this + 0x1a3c) * 4) = uVar2;
      *(int *)(this + 0x1a3c) = *(int *)(this + 0x1a3c) + 1;
    }
  }
  return;
}