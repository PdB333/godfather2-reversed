// FUNC_NAME: SomeClass::someMethod
void __thiscall SomeClass::someMethod(int *this, int param_2)
{
  int *piVar1;
  int iVar2;
  
  FUN_0087b790();
  iVar2 = _rand();
  if ((float)iVar2 * DAT_00e44590 < DAT_00d6471c) {
    (**(code **)(*this + 0x2ac))();
    return;
  }
  piVar1 = this + 0x395; // +0xE54: linked list pointer
  if (param_2 == 0) {
    param_2 = 0;
  }
  else {
    param_2 = param_2 + 0x48;
  }
  if (*piVar1 != param_2) {
    if (*piVar1 != 0) {
      FUN_004daf90(piVar1); // remove from linked list
    }
    *piVar1 = param_2;
    if (param_2 != 0) {
      this[0x396] = *(int *)(param_2 + 4); // +0xE58: next pointer
      *(int **)(param_2 + 4) = piVar1;
    }
  }
  if ((this[0x322] | 0x10000U) != this[0x322]) { // +0xC88: flags
    (**(code **)(this[0x16] + 0x28))(0x10); // +0x58: some vtable call
    this[0x322] = this[0x322] | 0x10000; // set flag bit 16
  }
  (**(code **)(*this + 0x298))(); // vtable call at +0x298
  return;
}