// FUNC_NAME: InputManager::queueControllerEvent
void __thiscall InputManager::queueControllerEvent(int thisPtr, undefined4 eventData)
{
  int currentCount;
  int totalCount;
  uint sumCounts;
  
  if ((*(byte *)(thisPtr + 0x100) & 1) != 0) {
    currentCount = *(int *)(thisPtr + 0x30);
    sumCounts = *(int *)(thisPtr + 0x9c) + *(int *)(thisPtr + 0x78) + *(int *)(thisPtr + 0x54) + currentCount;
    if ((sumCounts < 8) && (totalCount = FUN_0097b710(eventData), totalCount < 0)) {
      // Store event in queue at current position
      *(undefined4 *)(thisPtr + 0x10 + currentCount * 4) = eventData;
      *(int *)(thisPtr + 0x30) = *(int *)(thisPtr + 0x30) + 1;
      if (sumCounts == 0) {
        FUN_0097c5a0(); // Likely processFirstEvent or startProcessing
      }
    }
  }
  return;
}