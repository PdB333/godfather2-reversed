// FUNC_NAME: EARSRefCounted::setPtr
// Function address: 0x004dea40
// This is a smart pointer assignment operator/function that manages reference counting.
// It decrements the old reference (if any) and increments the new one.
// param_1 = this (pointer to smart pointer storage)
// param_2 = new pointer to assign

int * __thiscall setPtr(int *thisPtr, int *newPtr)
{
  int *oldObj;
  
  // If there's an existing object, decrement its reference count
  if (*thisPtr != 0) {
    oldObj = (int *)(*thisPtr + 4);  // +0x04: reference count field
    *oldObj = *oldObj + -1;           // Decrement ref count
    if (((int *)*thisPtr)[1] == 0) {  // If ref count reached zero
      (**(code **)(*(int *)*thisPtr + 4))();  // Call vtable destructor at +0x04 (vtable offset for destructor)
    }
    *thisPtr = 0;  // Clear old pointer
  }
  
  // Assign new pointer
  *thisPtr = (int)newPtr;
  
  // If new pointer is non-null, increment its reference count
  if (newPtr != 0) {
    *(int *)((int)newPtr + 4) = *(int *)((int)newPtr + 4) + 1;  // +0x04: reference count
  }
  
  return thisPtr;  // Return pointer to this smart pointer for chaining
}