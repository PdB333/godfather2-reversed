// FUNC_NAME: ChaseCamera::clampPositionToMaxDistance
void __thiscall ChaseCamera::clampPositionToMaxDistance(int this, float *targetPos)
{
  float dx;
  float dy;
  float dz;
  float dist;
  float scale;
  
  dx = *(float *)(this + 0x10) - *targetPos;
  dy = *(float *)(this + 0x14) - targetPos[1];
  dz = *(float *)(this + 0x18) - targetPos[2];
  dist = SQRT(dx * dx + dy * dy + dz * dz);
  // Check if distance is within valid range (between min and max)
  if ((_DAT_00d577a0 < dist) && (dist < *(float *)(this + 0x88))) {
    // Scale position to max distance from target
    scale = *(float *)(this + 0x88) / dist;
    *(float *)(this + 0x10) = scale * dx + *targetPos;
    *(float *)(this + 0x14) = scale * dy + targetPos[1];
    *(float *)(this + 0x18) = scale * dz + targetPos[2];
    // Also interpolate the camera's forward direction (z component)
    *(float *)(this + 0x1c) = scale * (*(float *)(this + 0x1c) - targetPos[3]) + targetPos[3];
  }
}