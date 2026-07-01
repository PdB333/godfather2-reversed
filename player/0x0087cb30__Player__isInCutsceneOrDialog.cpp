// FUNC_NAME: Player::isInCutsceneOrDialog
bool __fastcall Player::isInCutsceneOrDialog(int thisPtr)
{
  // Check if bit 1 of flags at +0xC88 is set (cutscene/dialog flag)
  if ((*(uint *)(thisPtr + 0xC88) >> 1 & 1) != 0) {
    return true;
  }
  
  // Check if there's an active dialog manager
  int dialogManager = FUN_0043b870(DAT_0113108c); // likely DialogTreeManager::getInstance()
  if (dialogManager != 0) {
    int dialogData = *(int *)(dialogManager + 0x48); // +0x48: current dialog data pointer
    if (dialogData != 0) {
      // Adjust pointer to get base of dialog object (offset -0x48)
      int dialogObj = dialogData + -0x48;
      if (dialogObj != 0) {
        return true; // Active dialog is playing
      }
    }
  }
  
  return false;
}