// FUNC_NAME: CameraManager::computeLookAtTarget
void CameraManager::computeLookAtTarget(float *outLookAt, float *inTarget)
{
  int cameraObj;
  float deltaX, deltaY, deltaZ;
  float unused;
  float lengthSq;

  cameraObj = FUN_00471610(); // likely getActiveCamera() or getCameraObject()
  deltaX = *inTarget - *(float *)(cameraObj + 0x30); // target.x - camera.position.x
  deltaZ = inTarget[2] - *(float *)(cameraObj + 0x38); // target.z - camera.position.z
  deltaY = 0.0;
  unused = 0;

  lengthSq = (float)FUN_0056afa0(&deltaX, &deltaX); // likely vectorLengthSquared or dot product
  if (lengthSq != (float)0) {
    // Normalize and compute look-at direction
    *outLookAt = DAT_00e44564 - deltaZ; // some constant minus deltaZ
    outLookAt[1] = deltaY;
    outLookAt[2] = deltaX;
    return;
  }
  // Fallback: copy camera's forward direction
  cameraObj = FUN_00471610();
  *(undefined8 *)outLookAt = *(undefined8 *)cameraObj; // copy first two floats (x,y)
  outLookAt[2] = *(float *)(cameraObj + 8); // copy z
  return;
}