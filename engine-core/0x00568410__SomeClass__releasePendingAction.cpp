// FUNC_NAME: SomeClass::releasePendingAction
void __thiscall SomeClass::releasePendingAction(int *this, undefined4 param2, undefined4 param3)
{
  char cVar1;
  int *piVar2;
  
  // Check if there are pending actions (at offsets +0x28 and +0x2C)
  if (this[10] != 0 || this[0xb] != 0) {
    // Call virtual function at vtable+0x8c to check if we can release
    cVar1 = (**(code **)(*this + 0x8c))();
    if (cVar1 != '\0') {
      // Get some manager/singleton via global function
      piVar2 = (int *)FUN_00ad8d40();
      if (piVar2 != (int *)0x0) {
        // Call virtual function at vtable+0x34 to get another object
        piVar2 = (int *)(**(code **)(*piVar2 + 0x34))();
        if (piVar2 != (int *)0x0) {
          // Call virtual function at vtable+0x10 to process the action
          (**(code **)(*piVar2 + 0x10))(this[10], this[0xb], param2, param3);
          // Clear the pending action slots
          this[10] = 0;
          this[0xb] = 0;
        }
      }
    }
  }
  return;
}