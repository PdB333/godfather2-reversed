// FUNC_NAME: MemoryManager::copyBlocks
int MemoryManager::copyBlocks(int src, int dst, int size)
{
  if (src == dst) {
    return size;
  }
  do {
    FUN_004d3e20(src); // copyBlock(src) - copies 0x10 bytes
    src = src + 0x10;
    size = size + 0x10;
  } while (src != dst);
  return size;
}