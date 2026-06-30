// FUNC_NAME: FileHandle::close
void __fastcall FileHandle::close(int thisPtr)
{
  // Check if the object at offset +0xC (pointer to file object) is non-null
  if (*(int *)(thisPtr + 0xc) != 0) {
    // Clear the 'inUse' flag at +0x40 of the file object
    *(int *)(*(int *)(thisPtr + 0xc) + 0x40) = 0;
    // Set the 'flags' field at +0x3C to 1 (likely 'closed' or 'invalid')
    uint *flags = (uint *)(*(int *)(thisPtr + 0xc) + 0x3c);
    *flags = *flags | 1;
    // Call the engine's close/deallocate function
    FUN_0064d670();
    // Clear the handle's pointer to the file object
    *(int *)(thisPtr + 0xc) = 0;
  }
}