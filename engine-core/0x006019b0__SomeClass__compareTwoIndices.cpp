// FUNC_NAME: SomeClass::compareTwoIndices
undefined4 __thiscall SomeClass::compareTwoIndices(int this, int *param_2, int *param_3)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  
  // Access element at index param_2: base + 0x70 + param_2 * 0xc
  piVar1 = (int *)(this + 0x70 + *param_2 * 0xc);
  iVar2 = *piVar1;  // First field at offset +0x00 within the element
  uVar6 = 0;
  if ((iVar2 != 0) && (iVar3 = piVar1[2], iVar3 != 0)) {  // Third field at offset +0x08
    // Access element at index param_3
    piVar1 = (int *)(this + 0x70 + *param_3 * 0xc);
    iVar4 = *piVar1;  // First field
    if ((iVar4 != 0) && ((iVar5 = piVar1[2], iVar5 != 0 && (iVar4 == iVar2)))) {
      // Both elements exist and have matching first fields, compare their third fields
      uVar6 = FUN_005f5ec0(iVar3, iVar5);
    }
  }
  return uVar6;
}