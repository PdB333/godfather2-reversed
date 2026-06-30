// FUNC_NAME: NetReflectable::releaseHandle
// WeakRef-like release function. Checks validity of the target object via a vtable call, 
// decrements the reference count in the control block, and calls destructor if count reaches zero.
// Returns a non-null pointer (address of local stack variable) if object was valid, or null if invalid/absent.
undefined1 * __fastcall NetReflectable::releaseHandle(uint this_unused, void *targetObject, int *controlBlock)

{
  int *refCountField;
  char isValid;
  uint returnDummy; // local_4 - used as a placeholder for a "true" pointer

  returnDummy = 0;
  if (controlBlock != (int *)0x0) {
    // vtable[2] (offset +8) is a validity check on targetObject
    isValid = (**(code (**)(void *))(*controlBlock + 8))(targetObject);
    if (isValid != '\0') {
      refCountField = controlBlock + 1; // +0x04: reference count
      *refCountField = *refCountField - 1;
      if (*refCountField == 0) {
        // vtable[1] (offset +4) is the destructor
        (**(code (**)(void))(*controlBlock + 4))();
      }
      return (undefined1 *)&returnDummy; // non-null indication
    }
    // Also decrement when the object is invalid (e.g., weak pointer expired)
    refCountField = controlBlock + 1;
    *refCountField = *refCountField - 1;
    if (*refCountField == 0) {
      (**(code (**)(void))(*controlBlock + 4))();
    }
  }
  return (undefined1 *)0x0; // null means release failed / already released
}