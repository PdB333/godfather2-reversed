// FUNC_NAME: SomeClass::releaseOrDecreaseRefCount
void __fastcall SomeClass::releaseOrDecreaseRefCount(int param_1)
{
  // Call a function with the object's data at +0x4 and +0x8
  // Possibly a destructor or cleanup function
  FUN_0088faf0(*(undefined4 *)(param_1 + 4), *(undefined4 *)(param_1 + 8));
  
  // Set refcount or some flag at +0xC to 0
  *(undefined4 *)(param_1 + 0xc) = 0;
  
  // If the value at +0x8 (size? count?) is greater than 1, call another function
  // Possibly free memory or deallocate
  if (1 < *(uint *)(param_1 + 8)) {
    FUN_009c8f10(*(undefined4 *)(param_1 + 4));
  }
  
  return;
}