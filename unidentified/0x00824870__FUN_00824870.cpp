// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, int param_2)

{
  int iVar1;
  
  // Call base class constructor at 0x0081f9f0
  FUN_0081f9f0(param_2);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d7343c;
  
  // Copy 16 bytes from param_2 + 0x4c to this + 0x13 (offset 0x4C)
  *(undefined8 *)(this + 0x13) = *(undefined8 *)(param_2 + 0x4c);
  *(undefined8 *)(this + 0x15) = *(undefined8 *)(param_2 + 0x54);
  
  // Copy int from param_2 + 0x5c to this + 0x17 (offset 0x5C)
  iVar1 = *(int *)(param_2 + 0x5c);
  this[0x17] = iVar1;
  
  // Initialize this + 0x18 to 0
  this[0x18] = 0;
  
  // If the copied pointer is non-null, update linked list
  if (iVar1 != 0) {
    // Copy value from iVar1 + 4 to this + 0x18
    this[0x18] = *(undefined4 *)(iVar1 + 4);
    // Update the next pointer in the linked list node
    *(undefined4 **)(iVar1 + 4) = this + 0x17;
  }
  
  // Copy int from param_2 + 0x64 (100 decimal) to this + 0x19
  this[0x19] = *(undefined4 *)(param_2 + 100);
  
  return this;
}