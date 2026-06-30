// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  int iVar1;
  int *piVar2;
  undefined4 *extraout_EDX;
  
  *this = &PTR_FUN_00e371e8;
  FUN_004ebba0(); // likely initializing some member
  FUN_004ebba0();
  FUN_004ebba0();
  FUN_004ebba0();
  FUN_004ebba0();
  *extraout_EDX = &PTR_FUN_00e37110;
  iVar1 = extraout_EDX[4]; // +0x10
  if (iVar1 != 0) {
    piVar2 = (int *)(DAT_01206880 + 0x14);
    *(undefined ***)*piVar2 = &PTR_LAB_01123be8;
    *piVar2 = *piVar2 + 4;
    *(int *)*piVar2 = iVar1;
    *piVar2 = *piVar2 + 4;
    extraout_EDX[4] = 0;
    extraout_EDX[5] = 0;
  }
  return;
}