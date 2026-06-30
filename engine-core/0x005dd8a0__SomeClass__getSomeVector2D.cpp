// FUNC_NAME: SomeClass::getSomeVector2D
void __thiscall getSomeVector2D(int this, uint flags, undefined4 *outVec)
{
  uint uVar1;
  undefined4 *unaff_EDI;
  
  flags = DAT_00f15b80 & flags;
  uVar1 = (DAT_00f15b78 | DAT_00f15b7c) & flags;
  if ((uVar1 != (DAT_00f15b78 | DAT_00f15b7c)) &&
     (((DAT_012056c0 & flags) != 0 ||
      ((uVar1 != 0 && ((*(uint *)(this + 700) & flags) == 0)))))) {
    *outVec = *(undefined4 *)(this + 0x28c);
    *unaff_EDI = *(undefined4 *)(this + 0x290);
    return;
  }
  *outVec = *(undefined4 *)(this + 0x284);
  *unaff_EDI = *(undefined4 *)(this + 0x288);
  return;
}