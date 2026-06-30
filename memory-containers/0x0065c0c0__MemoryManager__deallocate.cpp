// FUNC_NAME: MemoryManager::deallocate
void MemoryManager::deallocate(void *ptr, uint32_t size)
{
  // +0x00: ptr (param_2)
  // +0x04: size (param_3)
  // local_8 = ptr
  // local_4 = size
  FUN_0064b810(0x40, &ptr); // likely free() or pool deallocation with alignment flag 0x40
  return;
}