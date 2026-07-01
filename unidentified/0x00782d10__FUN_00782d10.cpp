// FUNC_NAME: SomeClass::setActive
void __thiscall SomeClass::setActive(int this, char isActive)
{
  int iVar1;
  
  if (isActive == '\0') {
    // Deactivating
    if ((*(byte *)(this + 0x74) & 1) != 0) {
      *(uint *)(this + 0x74) = *(uint *)(this + 0x74) & 0xfffffffe;
      FUN_004086d0(&DAT_0112ad84);
      if (*(int *)(this + 0xc) != 0) {
        iVar1 = FUN_0043b870(DAT_01131018);
        if (iVar1 != 0) {
          FUN_009af0a0(this + 0x10);
        }
      }
    }
  }
  else if ((*(byte *)(this + 0x74) & 1) == 0) {
    // Activating
    *(uint *)(this + 0x74) = *(uint *)(this + 0x74) | 1;
    if (DAT_0112ad84 != 0) {
      FUN_00408900(this, &DAT_0112ad84, 0x8000);
    }
    if (*(int *)(this + 0xc) != 0) {
      iVar1 = FUN_0043b870(DAT_01131018);
      if (iVar1 != 0) {
        FUN_009aefd0(this + 0x10, 0x8000);
        return;
      }
    }
  }
  return;
}