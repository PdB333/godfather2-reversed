// FUNC_NAME: InputManager::getLeftStickX
float InputManager::getLeftStickX(void)
{
  int controllerSlot;
  float leftStickX;
  
  controllerSlot = InputManager::getActiveController(); // 0x00471610
  // Check if left stick X and Y are within dead zone (DAT_00d5ef84 = dead zone threshold)
  // DAT_00e44680 = mask to extract absolute value or sign bit
  if (((float)((uint)*(float *)(controllerSlot + 0x20) & DAT_00e44680) < DAT_00d5ef84) &&
     ((float)(*(uint *)(controllerSlot + 0x28) & DAT_00e44680) < DAT_00d5ef84)) {
    return 0.0f; // Within dead zone, return 0
  }
  // Outside dead zone, return raw left stick X value
  leftStickX = *(float *)(controllerSlot + 0x20); // +0x20 = left stick X
  FUN_00b9a9fa(); // Likely a debug/logging call
  return leftStickX;
}