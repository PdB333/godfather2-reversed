// FUNC_NAME: SomeClass::someMethod
void SomeClass::someMethod(void)
{
  int iVar1;
  int in_EAX;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar1 = *(int *)(in_EAX + 0x1c); // this +0x1c: pointer to some internal structure
  local_10 = 0xffffffff; // -1 sentinel
  local_4 = 0; // null terminator or count
  local_c = *(undefined4 *)(iVar1 + 0x34); // save original value at +0x34
  local_8 = 0; // another null
  local_14 = *(undefined4 *)(iVar1 + 0x14); // save original value at +0x14
  *(undefined4 **)(iVar1 + 0x14) = &local_14; // replace pointer at +0x14 with address of local_14 (stack variable)
  FUN_006417c0(); // likely some initialization or processing function
  FUN_0063e400(); // another processing function
  return;
}