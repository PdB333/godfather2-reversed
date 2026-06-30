// FUNC_NAME: MemoryManager::initializeHeaps
void MemoryManager::initializeHeaps(void)
{
  // Allocate primary heap: 0x28000 bytes (163840)
  g_pPrimaryHeapBase = (undefined4 *)allocLargeBuffer(0x28000);
  
  // Allocate descriptor for primary heap (size 0x28 = 40 bytes)
  undefined4 *pPrimaryDesc = (undefined4 *)allocSmallObject(0x28);
  if (pPrimaryDesc != (undefined4 *)0x0) {
    pPrimaryDesc[0] = &HEAP_DESC_VTABLE; // +0x00: vtable pointer (class)
    memset(g_pPrimaryHeapBase, 0x28000, 0x40, 4); // Initialize heap memory
    pPrimaryDesc[9] = 1; // +0x24: initialization flag (1 = ready)
    setMemoryInitialized(0); // Update global state? (likely mutex or flag)
    g_pPrimaryHeapDescriptor = pPrimaryDesc;
  } else {
    g_pPrimaryHeapDescriptor = (undefined4 *)0x0;
  }

  // Allocate secondary heap: 0x7800 bytes (30720)
  g_pSecondaryHeapBase = (undefined4 *)allocLargeBuffer(0x7800);
  
  // Allocate descriptor for secondary heap (same type)
  undefined4 *pSecondaryDesc = (undefined4 *)allocSmallObject(0x28);
  if (pSecondaryDesc != (undefined4 *)0x0) {
    pSecondaryDesc[0] = &HEAP_DESC_VTABLE; // Same vtable
    memset(g_pSecondaryHeapBase, 0x7800, 0xc, 4); // Different fill pattern (0xc)
    pSecondaryDesc[9] = 1; // +0x24: initialization flag
    setMemoryInitialized(0);
    g_pSecondaryHeapDescriptor = pSecondaryDesc;
  } else {
    g_pSecondaryHeapDescriptor = (undefined4 *)0x0;
  }

  return;
}