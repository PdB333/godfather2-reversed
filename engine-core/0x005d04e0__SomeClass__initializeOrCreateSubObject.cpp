// FUNC_NAME: SomeClass::initializeOrCreateSubObject
int * __fastcall SomeClass::initializeOrCreateSubObject(int *thisPtr)
{
  int *newObj;
  int *oldObj;
  int someGlobal1;
  int someGlobal2;
  
  *thisPtr = 0;
  thisPtr[6] = 0;
  
  // Allocate 0x38 bytes (56 bytes) for a sub-object
  newObj = (int *)FUN_005c4410(0x38, 0);
  someGlobal1 = DAT_00e445a8;
  
  if (newObj == (int *)0x0) {
    newObj = (int *)0x0;
  }
  else {
    // Initialize the sub-object fields
    newObj[4] = 0x200;  // +0x10: some size/flag
    newObj[5] = 0x200;  // +0x14: some size/flag
    newObj[2] = someGlobal1;  // +0x08: store global value
    someGlobal2 = DAT_00e2b1a4;
    newObj[1] = 0;      // +0x04: initialize to zero
    newObj[3] = someGlobal2;  // +0x0C: store another global value
    newObj[6] = 0;      // +0x18: initialize to zero
    newObj[7] = 1;      // +0x1C: set to 1 (enabled/active)
    newObj[8] = 0;      // +0x20: initialize to zero
    newObj[9] = 1;      // +0x24: set to 1
    newObj[10] = 0;     // +0x28: initialize to zero
    newObj[0xb] = 0;    // +0x2C: initialize to zero
    newObj[0xc] = 0;    // +0x30: initialize to zero
    *newObj = (int)&PTR_FUN_00e3edc0;  // +0x00: vtable pointer
    newObj[0xd] = 0;    // +0x34: initialize to zero
  }
  
  // Replace the old sub-object pointer with the new one
  oldObj = (int *)*thisPtr;
  if (oldObj != newObj) {
    *thisPtr = (int)newObj;
    if (newObj != (int *)0x0) {
      // Call vtable function at offset 0 (constructor/init)
      (**(code **)*newObj)();
    }
    if (oldObj != (int *)0x0) {
      // Call vtable function at offset 4 (destructor/cleanup)
      (**(code **)(*oldObj + 4))();
    }
  }
  
  return thisPtr;
}