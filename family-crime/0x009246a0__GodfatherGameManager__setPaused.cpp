// FUNC_NAME: GodfatherGameManager::setPaused
void __thiscall GodfatherGameManager::setPaused(int *this, char isPaused)
{
  code *vtableEntry;
  
  if (isPaused != '\0') {
    // Pause: disable input, stop audio, hide UI elements, set pause state
    FUN_004c3930(); // InputManager::disableInput
    FUN_006a0710(); // AudioManager::pauseAll
    FUN_0090c960(this[0x1c]); // UIHud::hide (offset +0x70)
    FUN_0090d0c0(this[0x1d]); // UIMinimap::hide (offset +0x74)
    FUN_0090ce50(this[0x1e] == 1); // UIPauseMenu::show (offset +0x78)
    FUN_00698790(); // TimeManager::pause
    vtableEntry = *(code **)(*this + 0x2c);
    this[0x14] = 0; // m_pauseState = 0 (paused)
    (*vtableEntry)(); // virtual onPause()
    return;
  }
  // Unpause: enable input, resume audio, show UI, resume time
  FUN_00698760(); // TimeManager::unpause
  FUN_0090d130(); // UIMinimap::show
  FUN_004c3920(); // InputManager::enableInput
  vtableEntry = *(code **)(*this + 0x2c);
  this[0x14] = 0; // m_pauseState = 0 (unpaused)
  (*vtableEntry)(); // virtual onUnpause()
  return;
}