// FUNC_NAME: InputDeviceManager::setActiveDeviceSlot

int __fastcall InputDeviceManager::setActiveDeviceSlot(InputDeviceManager* this, int in_EAX)
{
  int result;
  InputDeviceManager* esi = this;
  
  // If the provided device pointer is not the current active device,
  // attempt to activate it via a validation/sub-activation function.
  if ((in_EAX != (int)esi) && (result = FUN_00665ce0(), result != 0)) {
    return result;
  }
  // Reset the active device slot index (offset +0x8) to 0 on failure or when same device.
  *(int *)((int)esi + 8) = 0;
  return 0;
}