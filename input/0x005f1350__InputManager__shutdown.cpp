// FUNC_NAME: InputManager::shutdown
undefined4 InputManager::shutdown(void)

{
  if ((gInputDevicesEnabled != 0) && (gInputDevices != 0)) {
    this->releaseDevices(); // FUN_005f5910 - likely releases input device resources
  }
  this->clearState(); // FUN_005f0e40 - resets the input manager state
  DAT_00e3f4d0 = 0; // sets global flag to 0 via FUN_005dbc10
  return 1;
}