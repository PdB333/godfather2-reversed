// FUNC_NAME: GlobalBufferManager::Reset
void __thiscall GlobalBufferManager::Reset(void)
{
  void *globalBuffer = g_globalBuffer; // DAT_01205968 - pointer to static buffer
  this->somePreReset(); // FUN_00616ed0 - likely prepares for reset
  if (this != 0) {
    this->somePostReset(); // FUN_009c8eb0 - finishes cleanup if instance exists
  }
  // Initialize the global buffer if it hasn't been initialized yet
  if (*(int *)((int)globalBuffer + 0x800) == 0) {
    // Redundant assignment (compiler artifact?), then memset whole buffer to 0
    *(int *)((int)globalBuffer + 0x800) = 0;
    memset(globalBuffer, 0, 0x800);
  }
}