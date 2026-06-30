// FUNC_NAME: InputManager::setControllerSlotMapping
void __thiscall InputManager::setControllerSlotMapping(int this, byte slotIndex, byte playerIndex)
{
  // +0x53d: currentSlotCount (byte)
  // +0x52d: slotToPlayerMapping[16] (byte array)
  if ((slotIndex < 0x10) && (slotIndex != *(byte *)(this + 0x53d))) {
    *(byte *)(slotIndex + 0x52d + this) = playerIndex;
  }
  return;
}