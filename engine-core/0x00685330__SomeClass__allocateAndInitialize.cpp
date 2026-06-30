// FUNC_NAME: SomeClass::allocateAndInitialize
undefined4 FUN_00685330(undefined4 param_1, undefined4 param_2)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = 2;   // size or type parameter
  local_8 = 0x10; // alignment or flags (16)
  local_4 = 0;    // additional parameter
  iVar1 = FUN_0043b980(0x2c0, &local_c, param_2); // allocate memory (size 0x2C0 = 704 bytes)
  if (iVar1 != 0) {
    uVar2 = FUN_006adb10(param_1); // initialize the allocated object
    return uVar2;
  }
  return 0;
}