// FUNC_NAME: EARSConnection::shutdown
void EARSConnection::shutdown()
{
  int *refCountPtr;
  int refCount;
  int *globalManager; // DAT_012234a8

  globalManager = (int *)DAT_012234a8;
  refCountPtr = *(int **)(this + 200); // +0xC8: pointer to reference-counted object (e.g., socketHandle)
  if (refCountPtr != (int *)0x0) {
    *refCountPtr = *refCountPtr - 1; // decrement reference count
    if (*refCountPtr == 0) {
      FUN_004d1ba0(refCountPtr); // free the object when count reaches zero
    }
    *(undefined4 *)(this + 200) = 0; // clear pointer
  }

  // Set connection state to 5 (likely kStateClosed or kStateDestroyed)
  *(undefined4 *)(this + 0xb0) = 5;

  // Stop any pending timer/callback (e.g., async send timeout)
  FUN_00ac3b80(*(undefined4 *)(this + 0xb8), FUN_004d19a0, this, 0);

  EnterCriticalSection((LPCRITICAL_SECTION)(globalManager + 0x68)); // +0x68: critical section for global manager

  // If this connection is the current active one, clear it
  if (this == *(EARSConnection **)(globalManager + 0x48)) { // +0x48: pointer to active connection
    *(undefined4 *)(globalManager + 0x48) = 0;
  }

  // If no active connection remains, resume normal processing
  if (*(int *)(globalManager + 0x48) == 0) {
    FUN_004d0870(); // likely resumes network poll/idle
  }

  LeaveCriticalSection((LPCRITICAL_SECTION)(globalManager + 0x68));
}