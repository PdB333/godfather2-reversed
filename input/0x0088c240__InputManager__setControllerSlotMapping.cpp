// FUNC_NAME: InputManager::setControllerSlotMapping
void __thiscall InputManager::setControllerSlotMapping(int thisPtr, int controllerIndex, uint slotIndex)
{
  int oldControllerIndex;
  uint slotMask;
  
  slotMask = slotIndex & 0xff;
  oldControllerIndex = *(int *)(thisPtr + 0xb0 + slotMask * 4); // +0xB0: controllerSlotMapping[16]
  if (controllerIndex != oldControllerIndex) {
    if (oldControllerIndex != 0) {
      FUN_0088a8e0(slotIndex); // clearControllerSlot? (slotIndex)
    }
    *(int *)(thisPtr + 0xb0 + slotMask * 4) = controllerIndex; // +0xB0: controllerSlotMapping[16]
    if (controllerIndex != 0) {
      // +0xC0: controllerSlotTimestamps[16]
      *(undefined4 *)(thisPtr + 0xc0 + slotMask * 4) = FUN_0088e830(thisPtr); // getCurrentTimeMs()
      if (((*(byte *)(*(int *)(thisPtr + 0xb0 + slotMask * 4) + 0x83) & 1) != 0) || // controller +0x83: flags & 1 (connected?)
         (*(char *)(slotMask + 0xbc + thisPtr) != '\0')) { // +0xBC: slotActiveFlags[16]
        FUN_0088b990(1, slotIndex); // setSlotActive(slotIndex, true)
      }
    }
  }
  return;
}