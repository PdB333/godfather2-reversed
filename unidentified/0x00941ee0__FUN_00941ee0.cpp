// FUNC_NAME: SomeClass::releaseOrDestructor
void __fastcall SomeClass::releaseOrDestructor(int *thisPtr)
{
  int vtablePtr;
  int *someManager;
  
  // Check if the object's signature (magic bytes at offsets 0x18-0x1b) is valid
  // If not valid, and the vtable pointer is non-null, call a cleanup function
  if (((((thisPtr[0x18] != -0x45245246) || (thisPtr[0x19] != -0x41104111)) ||
       (thisPtr[0x1a] != -0x153ea5ab)) || (thisPtr[0x1b] != -0x6eeff6ef)) &&
     (vtablePtr = *thisPtr, vtablePtr != 0)) {
    // Call some global cleanup function (likely memory manager or reference counting)
    FUN_004bfcf0();
    // Get a manager/singleton instance
    someManager = (int *)FUN_009c8f80();
    // Call a virtual function on the manager to release/deallocate the object
    // The function at vtable+4 takes the object pointer and a size (0xa0 = 160 bytes)
    (**(code **)(*someManager + 4))(vtablePtr, 0xa0);
  }
  // Clear the vtable pointer and the signature bytes
  *thisPtr = 0;
  thisPtr[0x1b] = 0;
  thisPtr[0x1a] = 0;
  thisPtr[0x19] = 0;
  thisPtr[0x18] = 0;
  return;
}