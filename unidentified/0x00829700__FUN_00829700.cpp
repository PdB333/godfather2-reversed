// FUNC_NAME: SomeClass::setSomeProperty
void SomeClass::setSomeProperty(int param_1)
{
  undefined4 *puVar1;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar1 = (undefined4 *)FUN_009c8f80(); // Get some global object pointer
  local_c = 2;  // Property type or command ID
  local_8 = 0x10; // Property value or size
  local_4 = 0;  // Additional parameter
  (**(code **)*puVar1)(param_1, &local_c); // Call virtual function on object with property data
  return;
}