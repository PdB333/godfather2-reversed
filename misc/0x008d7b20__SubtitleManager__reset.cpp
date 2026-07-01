// FUNC_NAME: SubtitleManager::reset
void __fastcall SubtitleManager::reset(undefined4 *thisSubtitleManager)
{
  *thisSubtitleManager = &PTR_FUN_00d7d6f8;
  thisSubtitleManager[3] = &PTR_LAB_00d7d6f4;  // +0x0C: vtable pointer for subtitle list? 
  FUN_004086d0(&DAT_012069d4);  // Release reference to subtitle font
  FUN_004086d0(&DAT_0112f9dc);  // Release background texture
  FUN_00408310(&DAT_0112f9dc);  // Delete background texture
  FUN_004086d0(&DAT_0112b36c);  // Release subtitle material
  thisSubtitleManager[0xf] = 0; // +0x3C: currentSubtitleCount = 0
  FUN_009c8f10(thisSubtitleManager[0xe]); // +0x38: Delete current subtitle text object
  thisSubtitleManager[0xe] = 0;  // +0x38: set to null
  thisSubtitleManager[0x10] = 0; // +0x40: subtitleTimer = 0
  if (thisSubtitleManager[0xb] != 0) { // +0x2C: if we have a background image
    FUN_009c8f10(thisSubtitleManager[0xb]);  // Delete it
  }
  thisSubtitleManager[3] = &PTR_LAB_00d7d6d8;
  DAT_0112999c = 0;  // Global active flag
  FUN_004083d0();    // Shutdown subtitles system
  return;
}