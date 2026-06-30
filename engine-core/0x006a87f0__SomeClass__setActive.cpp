// FUNC_NAME: SomeClass::setActive
void __thiscall SomeClass::setActive(int this, char active)
{
  int *piVar1;
  
  if (active == '\0') {
    if (*(char *)(this + 0x10) != '\0') {
      piVar1 = (int *)(this + 0x14);
      if (*(int *)(this + 0x14) != 0) {
        FUN_006a8100(*(int *)(this + 0x14),*(undefined4 *)(this + 0x1c),0,0,0);
      }
      if (*piVar1 != 0) {
        FUN_004daf90(piVar1);
        *piVar1 = 0;
      }
      *(undefined4 *)(this + 0x1c) = 0;
      *(undefined1 *)(this + 0x20) = 0;
      *(undefined1 *)(this + 0x10) = 0;
      return;
    }
  }
  else {
    *(undefined1 *)(this + 0x10) = 1;
  }
  return;
}