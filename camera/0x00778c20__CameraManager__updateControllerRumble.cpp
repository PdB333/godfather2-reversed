// FUNC_NAME: CameraManager::updateControllerRumble
void __fastcall CameraManager::updateControllerRumble(int thisPtr)
{
  int *controllerPtr;
  int *inputManagerPtr;
  int playerController;
  int cameraObj;
  int cameraObj2;
  uint someFlags;
  int extraArg;
  undefined4 ediReg;
  float rumbleDiff;
  float rumbleDiff2;
  double doubleTemp;
  undefined8 stackTransform;
  undefined4 stackTransform2;
  undefined1 stackBuffer[12];
  undefined4 stackDummy;
  uint stackFlags;
  float stackFloat;
  uint stackDummy2;
  undefined4 stackDummy3;
  undefined4 stackDummy4;
  
  controllerPtr = *(int **)(thisPtr + 0x5c);
  if (((controllerPtr != (int *)0x0) && (inputManagerPtr = (int *)FUN_0043b870(DAT_01131018), inputManagerPtr != (int *)0x0))
     && (playerController = (**(code **)(*inputManagerPtr + 0x34))(), playerController != 0)) {
    // Determine how to read the camera transform based on playerController state
    if ((*(int *)(playerController + 0x30) == 4) || (someFlags = FUN_0084d420(*(int *)(playerController + 0x30)), (someFlags & 8) != 0)) {
      stackTransform2 = *(undefined4 *)(playerController + 0x28);
      stackTransform = *(undefined8 *)(playerController + 0x20);
    }
    else if ((*(int *)(playerController + 4) == 0) || (*(int *)(playerController + 4) == 0x48)) {
      stackTransform2 = *(undefined4 *)(playerController + 0x1c);
      stackTransform = *(undefined8 *)(playerController + 0x14);
    }
    else {
      cameraObj = FUN_00471610();
      stackTransform = *(undefined8 *)(cameraObj + 0x30);
      stackTransform2 = *(undefined4 *)(cameraObj + 0x38);
    }
    cameraObj = FUN_00471610();
    cameraObj2 = FUN_00471610();
    FUN_007f7f30(&stackTransform, cameraObj2 + 0x30, cameraObj + 0x20, DAT_00d5f00c);
    stackDummy = 0;
    stackDummy2 = 0;
    stackDummy3 = 0;
    stackDummy4 = _DAT_00d5780c;
    (**(code **)(*controllerPtr + 0x90))(stackBuffer, controllerPtr + 0x1ba, 1);
    
    // Check rumble thresholds for the three components (extracted from stack)
    if (((DAT_00d5ef84 <= (float)(stackFlags & DAT_00e44680)) || (DAT_00d5ef84 <= (float)((uint)stackFloat & DAT_00e44680))) || (DAT_00d5ef84 <= (float)(stackDummy2 & DAT_00e44680))) {
      doubleTemp = (double)stackFloat;
      FUN_00b9a9fa();
      rumbleDiff = (float)doubleTemp;
    }
    else {
      rumbleDiff = 0.0;
    }
    cameraObj = FUN_00471610();
    if (((DAT_00d5ef84 <= (float)(*(uint *)(cameraObj + 0x20) & DAT_00e44680)) || (DAT_00d5ef84 <= (float)(*(uint *)(cameraObj + 0x24) & DAT_00e44680))) || (DAT_00d5ef84 <= (float)(*(uint *)(cameraObj + 0x28) & DAT_00e44680))) {
      doubleTemp = (double)*(float *)(cameraObj + 0x24);
      FUN_00b9a9fa();
      rumbleDiff2 = (float)doubleTemp;
    }
    else {
      rumbleDiff2 = 0.0;
    }
    // Apply rumble to the controller
    FUN_007f7540(rumbleDiff - rumbleDiff2, ediReg, _DAT_00d68354);
  }
  return;
}