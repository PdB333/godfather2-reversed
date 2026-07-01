// FUNC_NAME: SomeClass::setSomeFlags
void SomeClass::setSomeFlags(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar1 = (undefined4 *)FUN_009c8f80();  // Get some global structure pointer
  local_c = 2;  // Flag value 2
  local_8 = 0x10;  // Mask value 0x10
  local_4 = 0;  // Additional parameter
  (**(code **)*puVar1)(param_1,&local_c);  // Call function through vtable with parameters
  return;
}