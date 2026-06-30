// FUNC_NAME: MemoryManager::ensureCapacity
void MemoryManager::ensureCapacity(void)
{
  undefined4 uVar1;
  uint requestedSize;
  undefined4 oldBuffer;
  uint alignedSize;
  
  // Check if we need to grow the buffer
  if (g_maxSize < requestedSize) {
    // Align size up to next 16-byte boundary
    alignedSize = requestedSize + (0x10 - (requestedSize & 0xf));
    
    // Allocate new buffer (element size 0xc = 12 bytes per entry)
    oldBuffer = (*(code *)PTR__malloc_00f0cd88)(alignedSize * 0xc);
    
    // Save current buffer
    uVar1 = g_currentBuffer;
    
    // Point to new buffer
    g_currentBuffer = oldBuffer;
    
    // Copy existing data to new buffer (FUN_0065b420 handles copy)
    FUN_0065b420();
    
    // Restore old buffer pointer temporarily
    g_currentBuffer = uVar1;
    
    // Free old buffer
    (*(code *)PTR__free_00f0cd8c)(uVar1);
    
    // Update max size
    g_maxSize = alignedSize;
    
    // Set buffer to new allocation
    g_currentBuffer = oldBuffer;
  }
  return;
}