// FUNC_NAME: ChaseCamera::updateCameraDistance
void __fastcall ChaseCamera::updateCameraDistance(int this)
{
  float fVar1;
  float *pfVar2;
  float fVar3;
  float local_8;
  float local_4;
  
  // DAT_00e44598 is likely a global minimum distance threshold (e.g., minCameraDistance)
  // +0x40: current camera distance from target
  // +0x4c: minimum allowed camera distance
  if (DAT_00e44598 < *(float *)(this + 0x40) - *(float *)(this + 0x4c)) {
    fVar1 = *(float *)(this + 0x50); // +0x50: current camera distance (being interpolated)
    fVar3 = DAT_012067e8 * DAT_00d5d7b8; // product of two global time/frame values (e.g., deltaTime * speed)
    local_4 = *(float *)(this + 0x40) - fVar1; // difference between target distance and current distance
    local_8 = DAT_00e44564 - fVar3; // some global value minus the step
    if (fVar3 < local_4) {
      // Step is smaller than the remaining distance, just add the step
      *(float *)(this + 0x50) = fVar1 + fVar3;
      return;
    }
    pfVar2 = &local_8;
    if (DAT_00e44564 - fVar3 <= local_4) {
      pfVar2 = &local_4;
    }
    // Clamp the distance change to either the remaining distance or the global limit
    *(float *)(this + 0x50) = fVar1 + *pfVar2;
  }
  return;
}