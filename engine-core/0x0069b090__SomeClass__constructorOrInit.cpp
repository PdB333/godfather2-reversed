// FUNC_NAME: SomeClass::constructorOrInit
int SomeClass::constructorOrInit(int thisPtr, undefined4 *param2, undefined4 *param3)
{
  int local_20;
  undefined4 local_1c;
  int local_10;
  undefined4 local_c;
  
  // Call some function with param2[0], param2[1], a global data pointer, and 3
  FUN_004d3ca0(*param2, param2[1], &DAT_00d5ced8, 3);
  // Call some function with local_10, local_c, param3[0], param3[1]
  FUN_004d3ca0(local_10, local_c, *param3, param3[1]);
  // Initialize member at offset +0xC to 0
  *(undefined4 *)(thisPtr + 0xc) = 0;
  // Call some function with local_20, local_1c, another global data pointer, and 1
  FUN_004d3ca0(local_20, local_1c, &DAT_00e327b8, 1);
  // If local_20 is non-zero, call it as a function pointer (null dereference? bug?)
  if (local_20 != 0) {
    (*(code *)0x0)(local_20);
  }
  // If local_10 is non-zero, call it as a function pointer (null dereference? bug?)
  if (local_10 != 0) {
    (*(code *)0x0)(local_10);
  }
  return thisPtr;
}