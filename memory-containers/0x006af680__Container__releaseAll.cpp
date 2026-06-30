// FUNC_NAME: Container::releaseAll
void __fastcall Container::releaseAll(int thisPtr)
{
  // Loop decrement counter and call cleanup for each slot
  int count = *(int *)(thisPtr + 0xC); // +0xC: number of elements to clean up
  while (count = count - 1, count > -1)
  {
    // This calls some per-element cleanup function
    FUN_006b1900(); // Likely releases a managed resource
  }

  // Handle a smart pointer or shared object stored at +0x8
  int* pObject = *(int**)(thisPtr + 0x8); // +0x8: pointer to a shared/reference-counted object
  if (pObject != nullptr)
  {
    int* refCountPtr = pObject - 1; // offset -0x4 from object: reference count or allocation header
    if (*refCountPtr != 0)
    {
      // If reference count is non-zero, call a virtual method (likely a release/decrement with flag 3)
      void* vtable = *(void**)(pObject + 1); // +0x4 from object: vtable pointer
      (*(void(__thiscall**)(void*, int))vtable)(pObject, 3);
    }
    else
    {
      // Otherwise directly deallocate the memory block (including header)
      FUN_009c8f10((int)refCountPtr); // Freed memory includes the -4 header
    }
  }
}