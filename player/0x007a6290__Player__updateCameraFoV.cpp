// FUNC_NAME: Player::updateCameraFoV
void __thiscall Player::updateCameraFoV(int thisPtr, undefined4 *rotationMatrix, float deltaTime)
{
  char isPaused;
  int *enginePtr;
  float10 currentFov;
  float10 maxFov;
  
  isPaused = FUN_00481640(); // Check if game is paused
  if (isPaused != '\0') {
    FUN_007a01a0(*rotationMatrix, rotationMatrix[1], rotationMatrix[2], rotationMatrix[3], deltaTime);
    return;
  }
  if ((*(uint *)(thisPtr + 0x8e0) >> 0x17 & 1) == 0) { // Check bit 23 of flags at +0x8E0
    isPaused = FUN_0089c630(); // Check if player is aiming/zooming
    if (isPaused == '\0') {
      enginePtr = (int *)FUN_0043b870(DAT_01131018); // Get camera engine interface
      // Get current FOV from camera (virtual function at vtable+0x28)
      currentFov = (float10)(**(code **)(*enginePtr + 0x28))();
      // Get maximum FOV (virtual function at vtable+0x2c)
      maxFov = (float10)(**(code **)(*enginePtr + 0x2c))();
      if ((float10)(float)(currentFov + (float10)deltaTime) <= maxFov) {
        currentFov = (float10)(**(code **)(*enginePtr + 0x2c))(); // Clamp to max
      }
      else {
        currentFov = (float10)(float)(currentFov + (float10)deltaTime); // Increment toward max
      }
      // Set FOV (virtual function at vtable+0x3c)
      (**(code **)(*enginePtr + 0x3c))((float)currentFov);
      FUN_007a3760(&stack0xffffffec); // Update something related to FOV transition
    }
  }
  return;
}