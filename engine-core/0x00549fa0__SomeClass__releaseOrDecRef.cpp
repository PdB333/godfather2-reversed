// FUNC_NAME: SomeClass::releaseOrDecRef
void __fastcall SomeClass::releaseOrDecRef(undefined4 *thisPtr)
{
  // +0xC0 (0x30*4) offset: pointer to some ref-counted object (maybe a COM-style object or shared resource)
  undefined4 *refObj = (undefined4 *)thisPtr[0x30];
  
  // Set vtable pointer (common in destructor/release methods)
  *thisPtr = &PTR_FUN_00e39bc8;
  
  if (refObj != (undefined4 *)0x0) {
    // +0x04 (offset 4 from refObj): reference count (short)
    if (*(short *)(refObj + 1) != 0) {
      // +0x06 (offset 6 from refObj): decrement reference count (short)
      *(short *)((int)refObj + 6) = *(short *)((int)refObj + 6) - 1;
      if (*(short *)((int)refObj + 6) == 0) {
        // When reference count reaches zero, call release via vtable
        (**(code **)*refObj)(1);  // vtable[0] with parameter 1 (maybe 'delete' or 'release')
      }
    }
    // +0xC0: clear the pointer
    thisPtr[0x30] = 0;
  }
  return;
}