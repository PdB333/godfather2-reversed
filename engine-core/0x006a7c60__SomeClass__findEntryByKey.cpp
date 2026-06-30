// FUNC_NAME: SomeClass::findEntryByKey
undefined4 __thiscall SomeClass::findEntryByKey(int this, undefined4 param_2, int param_3, int param_4)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  
  uVar3 = (uint)((char)param_4 != '\0');
  if (param_3 != 0) {
    FUN_006a7890(&param_4, &param_3);
    if (param_4 != 0) {
      uVar3 = *(uint *)(param_4 + 4);
    }
  }
  if ((*(int *)(this + 0x434) != 0) && (uVar3 < *(uint *)(this + 0x2c))) {
    iVar1 = FUN_004dafd0(param_2);
    uVar2 = 0;
    if (*(uint *)(this + 0x28) != 0) {
      piVar4 = (int *)(this + 0x30);
      do {
        if (*piVar4 == iVar1) {
          return *(undefined4 *)(this + 0x34 + (uVar3 + uVar2 * 8) * 4);
        }
        uVar2 = uVar2 + 1;
        piVar4 = piVar4 + 8;
      } while (uVar2 < *(uint *)(this + 0x28));
      return 0;
    }
  }
  return 0;
}