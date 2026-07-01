// FUNC_NAME: InputManager::updateControllerSlotMapping
void __thiscall InputManager::updateControllerSlotMapping(int thisPtr, int slotIndex)
{
  char *slotDataPtr;
  int deviceHandle;
  uint slotLoop;

  if (slotIndex - 1U < 3) {
    // Set slot active flag at offset +0x7c + (slotIndex-1)*8
    *(undefined1 *)(thisPtr + 0x7c + (slotIndex - 1U) * 8) = 1;
  }
  slotLoop = 0;
  slotDataPtr = (char *)(thisPtr + 0x7c);
  while ((*(int *)(slotDataPtr + -4) == 0 || *slotDataPtr != '\0')) {
    slotLoop = slotLoop + 1;
    slotDataPtr = slotDataPtr + 8;
    if (2 < slotLoop) {
      if ((*(byte *)(thisPtr + 0xd0) >> 3 & 1) == 0) {
        FUN_00981ad0(thisPtr); // likely initializeDeviceSlots
        *(ushort *)(thisPtr + 0xd0) = *(ushort *)(thisPtr + 0xd0) | 8;
      }
      deviceHandle = FUN_008fe480(); // getCurrentDeviceHandle
      if (deviceHandle != *(int *)(thisPtr + 0xdc)) {
        FUN_008fddc0(); // disconnectCurrentDevice
        FUN_008fe5e0(deviceHandle); // connectToDevice
      }
      return;
    }
  }
  return;
}