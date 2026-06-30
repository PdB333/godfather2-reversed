// FUNC_NAME: InputManager::mapControllerButtonsToGameActions
uint __fastcall InputManager::mapControllerButtonsToGameActions(int this)
{
  uint flags;
  uint buttonState;
  
  buttonState = *(uint *)(this + 0x10); // +0x10: raw controller button state (XInput)
  flags = 0;
  
  // Map D-pad up (bit 5) to game action 0x20 (e.g., "up" or "navigate up")
  if ((buttonState >> 5 & 1) != 0) {
    flags = 0x20;
  }
  
  // Map D-pad down (bit 6) to game action 0x01 (e.g., "down" or "navigate down")
  if ((buttonState >> 6 & 1) != 0) {
    flags = flags | 1;
  }
  
  // Map left shoulder (bit 11) to game action 0x100 (e.g., "shoulder left" or "aim")
  if ((buttonState >> 0xb & 1) != 0) {
    flags = flags | 0x100;
  }
  
  // Map right shoulder (bit 12) to game action 0x04 (e.g., "shoulder right" or "fire")
  if ((buttonState >> 0xc & 1) != 0) {
    return flags | 4;
  }
  
  // Map left trigger (bit 13) to game action 0x08 (e.g., "trigger left" or "zoom")
  if ((buttonState >> 0xd & 1) != 0) {
    flags = flags | 8;
  }
  
  return flags;
}