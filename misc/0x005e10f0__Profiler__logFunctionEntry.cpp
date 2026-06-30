// FUNC_NAME: Profiler::logFunctionEntry
void __thiscall Profiler::logFunctionEntry(int thisPtr, int param2)
{
  int *bufferPtr;
  int *esiPtr; // unaff_ESI
  int retAddr; // unaff_retaddr
  int localStack[3]; // local_c, local_8, local_4

  // thisPtr +0x08 points to a fallback memory buffer (may be null)
  bufferPtr = *(int **)(thisPtr + 8);
  if (bufferPtr == (int *)0x0) {
    // If no fallback, use stack-local zeroed buffer
    localStack[0] = 0;
    localStack[1] = 0;
    localStack[2] = 0;
    bufferPtr = localStack;
  }

  // Call virtual allocator function (vtable[0]) with size 0x18 and hint pointer
  // The allocator returns a pointer to newly allocated memory (or reuses the hint)
  int (**vtable)(int, void*) = *(int (***)(int, void*))(thisPtr + 4);
  bufferPtr = (int *)vtable[0](0x18, bufferPtr);

  if (bufferPtr != (int *)0x0) {
    // Fill allocated block with profiler context:
    // offset 0x00: localStack[2] (usually 0 or saved value)
    bufferPtr[0] = localStack[2];
    // offset 0x04: return address (captured from stack)
    bufferPtr[1] = retAddr;
    // offset 0x08: parameter 2
    bufferPtr[2] = param2;
    // offset 0x0C: saved ESI register (likely this pointer of caller)
    bufferPtr[3] = *esiPtr;
    // offset 0x10: next word from ESI (part of saved context)
    bufferPtr[4] = esiPtr[1];
    // offset 0x14: null terminator or flags
    *(char *)(bufferPtr + 5) = 0;
    // offset 0x15: additional flag byte
    *(char *)((int)bufferPtr + 0x15) = 0;
  }
}