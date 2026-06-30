// FUNC_NAME: CameraManager::applyCameraShake
void CameraManager::applyCameraShake(Vector3* outShakeOffset)
{
  Vector3 shakeOffset;
  float randomScale;

  shakeOffset.x = 0.0f;
  shakeOffset.y = 0.0f;
  shakeOffset.z = 0.0f;
  shakeOffset.w = 0.0f; // +0x0C padding

  randomScale = getRandomFloat(); // FUN_0055a980 - returns 0..1
  if (DAT_00e446c8 < randomScale) { // threshold check (e.g. 0.5f)
    getShakeDirection(&shakeOffset); // FUN_0055aa00 - fills direction vector
    randomScale = getRandomFloat();
    shakeOffset.x *= randomScale;
    shakeOffset.y *= randomScale;
    shakeOffset.z *= randomScale;
  }

  outShakeOffset->x = shakeOffset.x;
  outShakeOffset->y = shakeOffset.y;
  outShakeOffset->z = shakeOffset.z;
  outShakeOffset->w = DAT_00e2b1a4; // +0x0C padding from global
  applyShakeToCamera(outShakeOffset, param_2); // FUN_0056d1f0
}