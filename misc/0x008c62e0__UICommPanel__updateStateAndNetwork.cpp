// FUNC_NAME: UICommPanel::updateStateAndNetwork
void __thiscall UICommPanel::updateStateAndNetwork(int thisPtr, int commPanelData)
{
  int iVar1;
  
  // Check if the comm panel state has connection active flag (bit 1)
  if ((*(byte *)(commPanelData + 4) & 3) != 0) {
    *(undefined1 *)(thisPtr + 0x15c) = 0; // Clear some flag at +0x15C
  }
  
  // Magic number check (0x637b907 = 104546055) – likely a network session ID or state
  if (*(int *)(thisPtr + 0x54) != 0x637b907) {
    FUN_008c48c0(commPanelData); // CommPanel::reset or initialize
  }
  
  iVar1 = *(int *)(commPanelData + 4); // Comm panel state enum
  if (iVar1 == 1) {
    // STATE_IDLE or CONNECTING
    FUN_008c2e10(commPanelData); // CommPanel::beginHandshake
    FUN_008be6e0(commPanelData); // CommPanel::sendConnectionRequest
    FUN_006b3fe0(thisPtr, commPanelData + 0x10, *(undefined1 *)(commPanelData + 0xc), 0); // UI::playAnimation
  }
  else {
    if (iVar1 == 2) {
      // STATE_CONNECTED or ESTABLISHED
      FUN_008c2e10(commPanelData); // CommPanel::beginHandshake (re-entrant? or update)
      if (_DAT_00d577a0 < *(float *)(thisPtr + 0x1e8)) { // Compare some global threshold with timer at +0x1E8
        FUN_008c1120(commPanelData); // CommPanel::showDisconnect
        return;
      }
      FUN_008c5ef0(commPanelData); // CommPanel::sendKeepAlive
      return;
    }
    if (iVar1 == 4) {
      // STATE_FAILED or DISCONNECTED
      FUN_008c14b0(commPanelData + 0x10, *(undefined4 *)(*(int *)(commPanelData + 8) + 0x38)); // CommPanel::showError with error code
    }
    *(undefined4 *)(thisPtr + 0x154) = 0; // Clear some UI state at +0x154
    iVar1 = FUN_008bdd00(commPanelData); // CommPanel::checkForTimeout
    if (-1 < iVar1) {
      FUN_008c2160(iVar1); // CommPanel::showTimeout
      return;
    }
  }
  return;
}