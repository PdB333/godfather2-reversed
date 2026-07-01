// FUNC_NAME: SomeClass::constructorWithArgs
void __thiscall SomeClass::constructorWithArgs(int *this, undefined4 param_2, undefined4 param_3, undefined4 param_4,
            undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8,
            undefined4 param_9)
{
  int *vtablePtr;
  int basePtr;
  
  basePtr = *this;
  // Set vtable pointer at offset +0x14 to a known vtable (PTR_LAB_00e573c4)
  **(undefined4 **)(basePtr + 0x14) = &PTR_LAB_00e573c4;
  vtablePtr = (int *)(basePtr + 0x14);
  *vtablePtr = *vtablePtr + 4; // Adjust vtable pointer (likely for multiple inheritance)
  
  // Call base class constructor or another initialization function
  FUN_009538c0(param_2, param_3, param_4, param_5, param_6, param_7, param_8, param_9);
  return;
}