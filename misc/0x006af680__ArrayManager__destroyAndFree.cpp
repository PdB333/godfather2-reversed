// FUNC_NAME: ArrayManager::destroyAndFree
void __thiscall ArrayManager::destroyAndFree(int this)
{
  int count;
  int buffer;
  
  count = *(int *)(this + 0xc); // Number of elements stored at +0xC
  while (count = count - 1, count > -1) // Loop from count-1 down to 0
  {
    FUN_006b1900(); // Call destructor/cleanup for each element (likely per-element cleanup)
  }
  
  buffer = *(int *)(this + 8); // Pointer to allocated buffer at +0x8
  if (buffer != 0)
  {
    // Check if there's a vtable pointer at buffer+4 (common EA allocator header)
    if (*(int *)(buffer - 4) != 0)
    {
      // Call virtual destructor via vtable[0] with argument 3
      (*(code *)**(undefined4 **)(buffer + 4))(3);
      return;
    }
    // Otherwise, free the memory block at the header (buffer-4)
    FUN_009c8f10(buffer - 4);
  }
  return;
}