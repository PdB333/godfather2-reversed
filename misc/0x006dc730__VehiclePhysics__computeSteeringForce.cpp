// FUNC_NAME: VehiclePhysics::computeSteeringForce
void __thiscall VehiclePhysics::computeSteeringForce(int this, float *outForce, float *targetPos, float *currentPos, int vehicleData, float deltaTime)
{
  float fVar1;
  float local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  
  // Check if handbrake is active (bit 0 at +0x8e3 in some component)
  if ((*(byte *)(*(int *)(this + 0x2d0) + 0x8e3) & 1) == 0) {
    // Normal steering: interpolate between maxSteeringAngle (+0x60) and minSteeringAngle (+0x80)
    local_18 = (*(float *)(vehicleData + 0x60) - *(float *)(vehicleData + 0x80)) * deltaTime +
               *(float *)(vehicleData + 0x80);
  }
  else {
    // Handbrake: use fixed steering angle at +0x154
    local_18 = *(float *)(vehicleData + 0x154);
  }
  
  // Compute direction vector from current to target, scaled by steering factor
  local_20 = (*targetPos - *currentPos) * local_18;
  local_1c = (targetPos[1] - currentPos[1]) * local_18;
  local_18 = (targetPos[2] - currentPos[2]) * local_18;
  
  // Clamp force magnitude to maxForce (+0x14)
  if (local_18 * local_18 + local_20 * local_20 + local_1c * local_1c <
      *(float *)(vehicleData + 0x14) * *(float *)(vehicleData + 0x14)) {
    local_14 = 0;
    // Normalize the direction vector (FUN_0056afa0 likely is a vector normalize function)
    FUN_0056afa0(&local_20, &local_20);
    fVar1 = *(float *)(vehicleData + 0x14);
    local_20 = local_20 * fVar1;
    local_1c = local_1c * fVar1;
    local_18 = local_18 * fVar1;
  }
  
  // Output the computed force
  *outForce = *currentPos + local_20;
  outForce[1] = currentPos[1] + local_1c;
  outForce[2] = currentPos[2] + local_18;
  return;
}