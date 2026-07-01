// FUNC_NAME: SomeClass::calculateTotalWeightedValue
undefined4 __fastcall calculateTotalWeightedValue(int *this)
{
  float fVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 local_8;
  
  iVar4 = this[2]; // +0x08: count of items
  iVar2 = 0;
  if (iVar4 != 0) {
    piVar3 = (int *)this[1]; // +0x04: pointer to array of item pointers
    do {
      iVar2 = iVar2 + *(int *)(*piVar3 + 200); // +0xC8: item's value field
      piVar3 = piVar3 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  fVar1 = (float)iVar2;
  if (iVar2 < 0) {
    fVar1 = fVar1 + DAT_00e44578; // rounding adjustment constant
  }
  local_8 = (undefined4)(longlong)ROUND(fVar1 * *(float *)(*this + 0x24)); // +0x24: multiplier
  return local_8;
}