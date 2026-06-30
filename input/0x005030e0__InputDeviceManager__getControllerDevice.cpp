// FUNC_NAME: InputDeviceManager::getControllerDevice
undefined4 InputDeviceManager::getControllerDevice(int controllerId)
{
  undefined4 result;
  
  // Check if controllerId is valid (non-zero)
  if (controllerId != 0) {
    // Access internal device data at offset 4: pointer to device table
    // Then offset 0xc from that table: device handler or index
    result = getDeviceState(*(undefined4 *)(*(int *)(this + 4) + 0xc));
    return result;
  }
  return 0;
}