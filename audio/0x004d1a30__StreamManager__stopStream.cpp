// FUNC_NAME: StreamManager::stopStream
void StreamManager::stopStream(void)
{
  int *piVar1;
  int iVar2;
  
  iVar2 = DAT_012234a8; // Global stream manager instance
  piVar1 = *(int **)(this + 0xc8); // +0xC8: current stream pointer
  if (piVar1 != (int *)0x0) {
    *piVar1 = *piVar1 + -1; // Decrement reference count
    if (*piVar1 == 0) {
      FUN_004d1ba0(piVar1); // Release stream (likely delete)
    }
    *(undefined4 *)(this + 0xc8) = 0; // Clear stream pointer
  }
  *(undefined4 *)(this + 0xb0) = 5; // +0xB0: stream state = 5 (stopped)
  FUN_00ac3b80(*(undefined4 *)(this + 0xb8),FUN_004d19a0,this,0); // Remove timer callback (FUN_004d19a0 is stream update)
  EnterCriticalSection((LPCRITICAL_SECTION)(iVar2 + 0x68)); // Lock stream manager critical section
  if (this == *(int *)(iVar2 + 0x48)) { // +0x48: active stream pointer
    *(undefined4 *)(iVar2 + 0x48) = 0; // Clear active stream
  }
  if (*(int *)(iVar2 + 0x48) == 0) { // No active stream
    FUN_004d0870(); // Stop stream manager processing
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(iVar2 + 0x68)); // Unlock
  return;
}