// FUNC_NAME: ControllerManager::updateControllerState
void __thiscall ControllerManager::updateControllerState(int this, ushort newButtonMask)
{
  bool bNeedUpdate;
  
  // Process button state changes for button 0 (bit 0)
  if ((newButtonMask & 1) == 0) {
    // Button 0 released
    if ((*(byte *)(this + 0x15c) & 1) != 0) {
      // Button 0 was previously pressed
      if ((*(uint *)(this + 0x60) >> 1 & 1) != 0) {
        // If trigger state was set, clear it
        *(uint *)(this + 0x60) = *(uint *)(this + 0x60) & 0xfffffffd;
        // Disable rumble for slot 0
        FUN_00977fa0(0);
      }
      // Clear pressed state for button 0
      *(ushort *)(this + 0x15c) = *(ushort *)(this + 0x15c) & 0xfffe;
    }
  }
  else if ((*(byte *)(this + 0x15c) & 1) == 0) {
    // Button 0 pressed (was not pressed before)
    if ((*(uint *)(this + 0x60) >> 1 & 1) == 0) {
      // If trigger state not set, set it
      *(uint *)(this + 0x60) = *(uint *)(this + 0x60) | 2;
      // Enable rumble for slot 0
      FUN_00977fa0(1);
    }
    // Set pressed state for button 0
    *(ushort *)(this + 0x15c) = *(ushort *)(this + 0x15c) | 1;
  }
  
  bNeedUpdate = false;
  
  // Process button state changes for button 1 (bit 1)
  if ((newButtonMask & 2) == 0) {
    // Button 1 released
    if ((*(byte *)(this + 0x15c) >> 1 & 1) != 0) {
      // Clear pressed state for button 1
      *(ushort *)(this + 0x15c) = *(ushort *)(this + 0x15c) & 0xfffd;
      goto LAB_00979ba4;
    }
  }
  else if ((*(byte *)(this + 0x15c) >> 1 & 1) == 0) {
    // Button 1 pressed (was not pressed before)
    *(ushort *)(this + 0x15c) = *(ushort *)(this + 0x15c) | 2;
LAB_00979ba4:
    bNeedUpdate = true;
  }
  
  // Process button state changes for button 2 (bit 2)
  if ((newButtonMask & 4) == 0) {
    // Button 2 released
    if ((*(byte *)(this + 0x15c) >> 2 & 1) == 0) goto LAB_00979bdc;
    // Clear pressed state for button 2
    *(ushort *)(this + 0x15c) = *(ushort *)(this + 0x15c) & 0xfffb;
  }
  else {
    // Button 2 pressed
    if ((*(byte *)(this + 0x15c) >> 2 & 1) != 0) goto LAB_00979bdc;
    // Set pressed state for button 2
    *(ushort *)(this + 0x15c) = *(ushort *)(this + 0x15c) | 4;
  }
  bNeedUpdate = true;
  
LAB_00979bdc:
  if (bNeedUpdate) {
    // If any of buttons 1 or 2 changed, force update
    if ((newButtonMask & 6) != 0) {
      FUN_00979090(newButtonMask & 6);
      return;
    }
    // Otherwise perform idle update
    FUN_00991cd0();
    FUN_00976d80(0);
  }
  return;
}