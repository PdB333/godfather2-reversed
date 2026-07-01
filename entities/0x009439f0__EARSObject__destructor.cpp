// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::destructor(undefined4 *this)
{
  int *refCountPtr;
  int *refCountDecrement;
  int vtablePtr;
  
  // Set vtable pointer to base destructor vtable
  *this = &PTR_FUN_00d8b42c;
  
  // Call base class destructor (likely EARS::Framework::Object or similar)
  FUN_004df600();
  
  // Decrement reference count
  refCountPtr = (int *)this[3];  // +0x0C: reference count pointer
  refCountDecrement = refCountPtr + 1;
  *refCountDecrement = *refCountDecrement + -1;
  
  // If reference count reaches zero, call destructor via vtable
  if (*refCountDecrement == 0) {
    (**(code **)(*refCountPtr + 4))();  // Call virtual destructor
  }
  
  // Clear child pointer (likely a linked list or child object)
  vtablePtr = this[2];  // +0x08: child/next pointer
  if (vtablePtr != 0) {
    *(undefined4 *)(vtablePtr + 8) = 0;  // Clear back pointer
    this[2] = 0;
  }
  
  return;
}