// FUNC_NAME: EventDispatcher::fireAllPending
void __thiscall EventDispatcher__fireAllPending(void *this, uint param_1)
{
  int *eventPtr;
  uint eventIndex;
  
  eventIndex = 0;
  if (*(int *)((int)this + 8) != 0) {
    do {
      eventPtr = *(int **)(*(int *)((int)this + 4) + eventIndex * 8);
      if ((char)eventPtr[8] != '\0') {
        (**(code **)(*eventPtr + 8))(param_1);
      }
      eventIndex = eventIndex + 1;
    } while (eventIndex < *(uint *)((int)this + 8));
  }
  return;
}