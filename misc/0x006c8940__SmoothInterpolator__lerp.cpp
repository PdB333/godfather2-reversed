// FUNC_NAME: SmoothInterpolator::lerp
void __thiscall SmoothInterpolator::lerp(float *currentPos, float *targetPos, float t, float *outPos)
{
  float targetY = targetPos[1];
  float targetZ = targetPos[2];
  float speedFactor = *(float *)(this + 0x60); // +0x60: interpolation speed multiplier
  float adjustedT = speedFactor * t;
  float currentY = currentPos[1];
  float currentZ = currentPos[2];

  outPos[0] = currentPos[0] + (targetPos[0] - currentPos[0]) * adjustedT;
  outPos[1] = currentY + (targetY - currentY) * adjustedT;
  outPos[2] = currentZ + (targetZ - currentZ) * adjustedT;
}