// FUNC_NAME: StreamManager::retainStream
uint StreamManager::retainStream(void)
{
  uint uVar1;
  
  uVar1 = DAT_00d5ccf8; // g_someManager
  if (*(int *)(this + 0x20c) == 0) {
    // Clear bit 16 (0x10000) at offset 0x18c (likely active/paused flag)
    *(uint *)(this + 0x18c) = *(uint *)(this + 0x18c) & 0xfffeffff;
    FUN_008b8f10(0, uVar1); // Some manager operation (e.g., startPlayback)
    // Increment reference count
    *(int *)(this + 0x20c) = *(int *)(this + 0x20c) + 1;
    return 0; // First retain
  }
  // Already retained, just increment
  *(int *)(this + 0x20c) = *(int *)(this + 0x20c) + 1;
  return 1; // Subsequent retain
}