// FUN_004a70f0: EARSVideoManager::setScreenBufferProperties
void EARSVideoManager::setScreenBufferProperties(void)
{
  // +0x00: vtable pointer
  // Get the singleton instance of the video manager (likely EA::EARS::VideoManager)
  uint32_t* videoManager = (uint32_t*)FUN_009c8f80(); // singleton getter
  // Command parameters: mode (2), width/height (0x10), flags (0)
  // This might set a screen buffer size or resolution mode
  int32_t params[3] = { 2, 0x10, 0 }; // local_c=2, local_8=0x10, local_4=0
  // Call virtual function at index 0 (first in vtable) with command 0xA0 and parameters
  (*(void(__thiscall*)(uint32_t*, int32_t, int32_t*))(*(uint32_t*)(*videoManager)))(videoManager, 0xA0, params);
}