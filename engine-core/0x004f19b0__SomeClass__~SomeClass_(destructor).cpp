// FUNC_NAME: SomeClass::~SomeClass (destructor)
undefined4 * __thiscall SomeClass::~SomeClass(undefined4 *this, byte flags)

{
  int iVar1;
  int *piVar2;
  
  *this = &PTR_FUN_00e37110;
  iVar1 = this[4];
  if (iVar1 != 0) {
    piVar2 = (int *)(DAT_01206880 + 0x14);
    *(undefined ***)*piVar2 = &PTR_LAB_01123be8;
    *piVar2 = *piVar2 + 4;
    *(int *)*piVar2 = iVar1;
    *piVar2 = *piVar2 + 4;
    this[4] = 0;
    this[5] = 0;
  }
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}