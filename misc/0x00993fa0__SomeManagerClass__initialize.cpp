// FUNC_NAME: SomeManagerClass::initialize
void __fastcall SomeManagerClass::initialize(undefined4 *this)
{
  int *piVar1;
  
  *this = &PTR_FUN_00d92234;
  this[1] = &PTR_LAB_00d92230;
  FUN_00607d50(0, &LAB_00993a50);
  if (DAT_01130944 != 0) {
    FUN_006065a0(DAT_01130944, 0);
  }
  DAT_01130944 = 0;
  piVar1 = (int *)(DAT_01206880 + 0x14);
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_00e576e4;
  *piVar1 = *piVar1 + 4;
  *(undefined4 **)*piVar1 = this;
  *piVar1 = *piVar1 + 4;
  this[1] = &PTR_LAB_00d92220;
  DAT_0113094c = 0;
  *this = &PTR_LAB_00e3e74c;
  return;
}