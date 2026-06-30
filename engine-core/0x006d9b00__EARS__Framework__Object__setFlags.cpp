// FUNC_NAME: EARS::Framework::Object::setFlags
void EARS::Framework::Object::setFlags(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  // Get the vtable pointer for the object
  puVar1 = (undefined4 *)FUN_009c8f80(); // Likely EARS::Framework::Object::getVTable or similar
  // Set up a structure with flag values: 2 (0x2), 16 (0x10), 0
  local_c = 2; // Flag value 1: 0x2
  local_8 = 0x10; // Flag value 2: 0x10
  local_4 = 0; // Flag value 3: 0
  // Call the vtable function at index 0 (likely setFlags or similar)
  (**(code **)*puVar1)(param_1,&local_c);
  return;
}