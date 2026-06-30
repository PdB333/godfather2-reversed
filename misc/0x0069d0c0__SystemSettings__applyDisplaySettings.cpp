// FUNC_NAME: SystemSettings::applyDisplaySettings
void SystemSettings::applyDisplaySettings(void)
{
  int isFullscreen;
  uint local_4;
  uint displayFlags;
  
  isFullscreen = FUN_006a17c0(); // Check if fullscreen mode is supported
  if (isFullscreen == 0) {
    SystemParametersInfoA(0xb, 0, (PVOID)0x0, 1); // SPI_SETSCREENSAVEACTIVE - disable screensaver
  }
  
  // Apply first display setting (e.g., resolution or refresh rate)
  displayFlags = DAT_00e50b44; // +0x00: display setting value
  if ((DAT_00e50b48 & 1) == 0) { // +0x04: display flags (bit 0 = enabled)
    local_4 = DAT_00e50b48 & 0xfffffff3; // Clear bits 2-3 (e.g., vsync or mode flags)
    SystemParametersInfoA(0x3b, 8, &displayFlags, 0); // SPI_SETDISPLAYCHANGE - apply display change
  }
  
  // Apply second display setting (e.g., color depth or another mode)
  displayFlags = DAT_00e50b4c; // +0x08: another display setting value
  local_4 = DAT_00e50b50; // +0x0C: another display flags
  if ((DAT_00e50b50 & 1) == 0) {
    local_4 = DAT_00e50b50 & 0xfffffff3;
    SystemParametersInfoA(0x3b, 8, &displayFlags, 0);
  }
  
  FUN_0069cfb0(); // Apply final display settings (e.g., refresh rate)
  SystemParametersInfoA(0xf, 0, (PVOID)0x0, 0); // SPI_SETSCREENSAVEACTIVE - re-enable screensaver
  return;
}