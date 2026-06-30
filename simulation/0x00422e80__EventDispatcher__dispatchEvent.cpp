// FUNC_NAME: EventDispatcher::dispatchEvent
void __thiscall EventDispatcher::dispatchEvent(int thisPtr, int param0, int param1)
{
  // Store event parameters into the object
  *(int *)(thisPtr + 0x144) = param0;
  *(int *)(thisPtr + 0x148) = param1;

  // Call base class / internal event propagation
  EventDispatcher::baseDispatch();

  // Thread-local check – likely a recursion guard or processing flag
  int *tlsPtr = *(int **)(*(int *)(__readfsdword(0x2c)) + 0x34);
  if (tlsPtr == 0)
  {
    // Global event queue buffer pointer (bump allocator)
    int **allocPtr = (int **)(g_eventQueueAllocator + 0x14);  // &(globalAllocator->current)
    // Write vtable pointer for the event entry
    **allocPtr = (int)&g_eventEntryVTable;  // PTR_LAB_0110b6a4
    // Advance past vtable
    *allocPtr = *allocPtr + 1;
    // Write this pointer
    **allocPtr = thisPtr;
    int entryBase = *allocPtr;
    // Write event parameters
    *(int *)(entryBase + 4) = param0;
    *(int *)(entryBase + 8) = param1;
    // Advance allocator pointer by 12 (total entry: vtable(4) + this(4) + param0(4) + param1(4) = 16)
    *allocPtr = (int *)((int)entryBase + 0xc);
  }
}