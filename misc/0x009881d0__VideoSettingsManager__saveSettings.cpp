// FUNC_NAME: VideoSettingsManager::saveSettings
void __fastcall VideoSettingsManager::saveSettings(VideoSettingsManager* this)
{
  if ((*(char*)(this + 0x10d) != '\0') && (*(int*)(this + 0x58) == 1)) {
    // Save video resolution, refresh rate, and fullscreen state
    FUN_0069bf90("Window.Width", *(int*)(this + 0x114));     // +0x114: screen width
    FUN_0069bf90("Window.Height", *(int*)(this + 0x110));    // +0x110: screen height
    FUN_0069bf90("Window.Hz", *(int*)(this + 0x118));        // +0x118: refresh rate
    FUN_0069bf00("Window.FullScreen", *(int*)(this + 0x70) == 0); // +0x70: fullscreen flag (0 = fullscreen)
    FUN_0090cb20(*(int*)(this + 0x78), 0);                   // +0x78: window mode or similar
  }
  FUN_0069ff90(1);   // Flush config or sync
  FUN_00698790();    // UI or display update
  *(char*)(this + 0x10c) = 0;   // Clear dirty flag for something
  *(char*)(this + 0x10d) = 0;   // Clear dirty flag for video settings
}