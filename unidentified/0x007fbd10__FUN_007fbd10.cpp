// FUNC_NAME: SomeClass::setAndInterpolateQuaternion
void SomeClass::setAndInterpolateQuaternion(int thisPtr, undefined4 *newQuat, undefined4 param3)
{
  undefined4 oldW, oldX, oldY, oldZ;
  undefined4 newW, newX, newY, newZ;
  undefined4 local_30, local_2c, local_28, local_24, local_20, local_1c;
  
  // Save old quaternion components from +0x40 to +0x4c
  oldX = *(undefined4 *)(thisPtr + 0x40);  // +0x40: quaternion x
  oldY = *(undefined4 *)(thisPtr + 0x44);  // +0x44: quaternion y
  oldZ = *(undefined4 *)(thisPtr + 0x48);  // +0x48: quaternion z
  oldW = *(undefined4 *)(thisPtr + 0x4c);  // +0x4c: quaternion w
  
  // Set new quaternion from input
  *(undefined4 *)(thisPtr + 0x40) = *newQuat;       // new x
  *(undefined4 *)(thisPtr + 0x44) = newQuat[1];     // new y
  *(undefined4 *)(thisPtr + 0x48) = newQuat[2];     // new z
  *(undefined4 *)(thisPtr + 0x4c) = newQuat[3];     // new w
  
  // Build old quaternion on stack for interpolation
  local_30 = oldX;
  local_2c = oldY;
  local_28 = oldZ;
  local_24 = oldW;
  
  // Call interpolation function at +0xc0 with old quat and some parameter
  FUN_009e7fd0(thisPtr + 0xc0, &local_30, param3, param3);
  
  // Restore old quaternion (interpolation was done on the side)
  *(undefined4 *)(thisPtr + 0x40) = oldX;
  *(undefined4 *)(thisPtr + 0x44) = oldY;
  *(undefined4 *)(thisPtr + 0x48) = oldZ;
  *(undefined4 *)(thisPtr + 0x4c) = oldW;
  
  return;
}