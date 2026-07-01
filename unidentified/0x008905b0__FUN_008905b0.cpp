// FUNC_NAME: SomeClass::resetOrInitFunction
void SomeClass::resetOrInitFunction(int param_1)
{
  // Call a function with the two fields at +0x04 and +0x08
  FUN_0088faf0(*(undefined4 *)(param_1 + 4), *(undefined4 *)(param_1 + 8));
  
  // Set field at +0x0C to 0
  *(undefined4 *)(param_1 + 0xc) = 0;
  
  // If the value at +0x08 is greater than 1, call another function with the field at +0x04
  if (1 < *(uint *)(param_1 + 8)) {
    FUN_009c8f10(*(undefined4 *)(param_1 + 4));
  }
  
  // Set fields at +0x10, +0x14, +0x18 to specific values
  *(undefined4 *)(param_1 + 0x10) = _DAT_00d5780c;  // Global data
  *(undefined4 *)(param_1 + 0x14) = DAT_00d5eee4;   // Global data
  *(undefined4 *)(param_1 + 0xc) = 0;                // Reset to 0 again
  *(undefined4 *)(param_1 + 0x18) = 0;               // Set to 0
  
  // Set field at +0x08 to 1
  *(undefined4 *)(param_1 + 8) = 1;
  
  // Set pointer at +0x04 to a global data address
  *(undefined4 **)(param_1 + 4) = &DAT_00ef4398;
  
  return;
}