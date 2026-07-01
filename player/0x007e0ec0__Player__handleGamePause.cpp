// FUNC_NAME: Player::handleGamePause
void __fastcall Player::handleGamePause(int this)
{
  int gameManager;
  char isPaused;
  int *inputManager;
  
  gameManager = *(int *)(this + 0x58); // +0x58: pointer to GodfatherGameManager
  isPaused = FUN_00481640(); // likely GodfatherGameManager::isPaused or similar
  if (isPaused == '\0') {
    inputManager = (int *)FUN_007ab170(); // likely InputDeviceManager::getInstance or similar
    if ((*(uint *)(gameManager + 0x8e0) >> 0x17 & 1) != 0) { // +0x8e0: some flags bitfield, bit 23 = something
      (*(code *)((undefined4 *)*inputManager)[1])(); // call second vtable entry (likely resumeInput or similar)
      return;
    }
    (**(code **)*inputManager)(1); // call first vtable entry with arg 1 (likely pauseInput or similar)
  }
  return;
}