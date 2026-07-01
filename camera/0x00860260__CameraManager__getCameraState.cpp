// FUNC_NAME: CameraManager::getCameraState
void __thiscall CameraManager::getCameraState(int thisPtr, undefined8 *outPosition, undefined8 *outTarget, undefined4 *outFov)
{
  // Check if camera is active (bit 15 of flags at +0xf28)
  if ((*(uint *)(thisPtr + 0xf28) >> 0xf & 1) == 0) {
    // Camera not active, initialize default state
    FUN_00860170();
  }
  
  // Copy camera position (Vec3 at +0xfa8, 12 bytes)
  *outPosition = *(undefined8 *)(thisPtr + 0xfa8);
  *(undefined4 *)(outPosition + 1) = *(undefined4 *)(thisPtr + 0xfb0);
  
  // Copy camera target/lookAt (Vec3 at +0xfb4, 12 bytes)
  *outTarget = *(undefined8 *)(thisPtr + 0xfb4);
  *(undefined4 *)(outTarget + 1) = *(undefined4 *)(thisPtr + 0xfbc);
  
  // Copy field of view (float at +0xfc0)
  *outFov = *(undefined4 *)(thisPtr + 0xfc0);
  
  return;
}