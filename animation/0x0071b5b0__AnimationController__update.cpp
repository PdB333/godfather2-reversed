// FUNC_NAME: AnimationController::update

void __thiscall AnimationController::update(int this, float deltaTime)
{
  int entityPtr;
  int characterPtr;
  float var1;
  char isActive;
  int *someGlobalPtr;
  int playerPtr;
  float playerFloat;
  
  preUpdate(deltaTime);
  entityPtr = *(int *)(this + 0x10);
  characterPtr = *(int *)(this + 0xc);
  if (entityPtr == 0) goto LAB_0071b6a8;
  isActive = isCharacterActive(characterPtr);
  if (isActive == '\0') {
LAB_0071b678:
    isActive = canUpdateCharacter(*(int *)(this + 0xc));
    if ((isActive != '\0') &&
       ((*(float *)(this + 0x50) <= deltaTime && deltaTime != *(float *)(this + 0x50) ||
        ((*(uint *)(characterPtr + 0x249c) >> 2 & 1) == 0)))) {
      updateAnimation(entityPtr);
    }
  }
  else {
    isActive = isGamePaused();
    if (isActive == '\0') {
      if (*(int *)(this + 0xc) == 0) {
        someGlobalPtr = (int *)0x0;
      }
      else {
        someGlobalPtr = (int *)getPlayerManager(DAT_01131018);
      }
      playerPtr = (**(int (**)(void))(*someGlobalPtr + 0x34))();
      playerFloat = (float)*(int *)(playerPtr + 0x40);
      if (*(int *)(playerPtr + 0x40) < 0) {
        playerFloat = playerFloat + DAT_00e44578;
      }
      if (playerFloat * DAT_00d5efb8 < *(float *)(this + 0x4c)) goto LAB_0071b678;
    }
    *(uint *)(this + 0x3c) = *(uint *)(this + 0x3c) | 1;
    updateAnimation(entityPtr);
    if (*(int *)(this + 0x20) == entityPtr) {
      playAnimation(0);
    }
    unsigned int regionId = 0;
    unsigned int context = getDebugRegion(0,0);
    logDebugEvent(0x18c62729,0,context,regionId);
    endDebugRegion();
  }
LAB_0071b6a8:
  postUpdate(deltaTime);
  *(float *)(this + 0x4c) = deltaTime;
  return;
}