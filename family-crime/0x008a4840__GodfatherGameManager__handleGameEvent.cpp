// FUNC_NAME: GodfatherGameManager::handleGameEvent
void __thiscall GodfatherGameManager::handleGameEvent(int this, int *eventData)
{
  int eventType;
  
  eventType = *eventData;
  if (eventType == DAT_01206a20) {
    // Check if game is in a state where we should show the "Don't leave" warning
    if ((*(int *)(DAT_01223484 + 0xc) != 0) || ((*(uint *)(DAT_01223484 + 0x37c) >> 5 & 1) != 0)) {
      FUN_0093c210(); // likely showWarningDialog
      if (DAT_0112ee84 != 0) {
        FUN_00408900(this, &DAT_0112ee84, 0x8000); // likely sendEventToUI
      }
    }
    // Check if any crew member is in combat (offsets +0x44 to +0x50)
    if (((((*(int *)(DAT_0112b9b4 + 0x44) != 0) || (*(int *)(DAT_0112b9b4 + 0x48) != 0)) ||
         (*(int *)(DAT_0112b9b4 + 0x4c) != 0)) || (*(int *)(DAT_0112b9b4 + 0x50) != 0)) &&
       ((*(int *)(DAT_0112b9b4 + 0x40) == 0 && (*(int *)(this + -0x358) != 0)))) {
      FUN_008b0a30(); // likely handleCombatState
      return;
    }
  }
  else {
    if (eventType == DAT_0112ee84) {
      FUN_0093a2f0(); // likely handleUIEvent
      FUN_004086d0(&DAT_0112ee84); // likely destroyUIElement
      return;
    }
    if (eventType == DAT_0112ee7c) {
      if (*(int *)(this + -0x358) != 0) {
        (**(code **)(*(int *)(this + -0x360) + 0x88))(); // likely call virtual function at vtable+0x88
        return;
      }
    }
    else {
      FUN_004bf710(eventData); // likely default event handler
    }
  }
  return;
}