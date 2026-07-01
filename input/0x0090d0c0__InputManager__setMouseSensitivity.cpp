// FUNC_NAME: InputManager::setMouseSensitivity
void __thiscall InputManager::setMouseSensitivity(int thisPtr, int sensitivity)
{
  float fVar1;
  int iVar2;
  
  fVar1 = DAT_00d5c454; // global mouse sensitivity multiplier
  if (sensitivity < 1) {
    sensitivity = 0;
  }
  else if (9 < sensitivity) {
    sensitivity = 10;
  }
  *(int *)(thisPtr + 0x3c) = sensitivity; // +0x3c: mouseSensitivity
  iVar2 = FUN_00411070(*(undefined1 *)(DAT_012233b4 + 0x564)); // getInputDeviceManager
  *(float *)(iVar2 + 0x11c) = (float)sensitivity * fVar1 + fVar1; // +0x11c: mouseSensitivityScaled
  FUN_0069bf90("Mouse.Sensitivity",sensitivity); // save to config
  return;
}