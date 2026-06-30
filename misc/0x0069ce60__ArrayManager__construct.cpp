// FUNC_NAME: ArrayManager::construct
void * __fastcall ArrayManager::construct(ArrayManager *this)
{
  int totalSize;

  // Global count/size multiplier
  totalSize = g_arrayCount * 8;

  // Store pointer to global instance
  g_arrayManagerInstance = this;

  // Set vtable pointer
  this->vtable = &s_ArrayManagerVtable;

  // Initialize the array buffer: from start to end, with element count = totalSize >> 3 = g_arrayCount
  // This likely calls a memset or placement-new for each element (8 bytes each)
  ArrayManager::initializeBuffer(g_arrayBuffer, g_arrayBuffer + totalSize, totalSize >> 3);

  return this;
}