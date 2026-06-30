// FUNC_NAME: EARS::MemoryManager::resolvePointer
int __fastcall EARS::MemoryManager::resolvePointer(uint ptr)
{
  // Check if the pointer is in the first memory pool (0x80000000 flag)
  if ((ptr & 0xc0000000) == 0x80000000) {
    // Direct offset: multiply by 4 to get the actual address
    return ptr * 4;
  }
  // Check if the pointer is in the second memory pool (0xC0000000 flag)
  if ((ptr & 0xc0000000) != 0xc0000000) {
    // Not a valid compressed pointer
    return 0;
  }
  // Second pool: offset into a base table at 0x60
  return *(int *)(ptr * 4 + 0x60);
}