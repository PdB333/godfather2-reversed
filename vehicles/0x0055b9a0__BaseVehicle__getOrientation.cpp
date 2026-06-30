// FUNC_NAME: BaseVehicle::getOrientation
void __thiscall BaseVehicle::getOrientation(int this, Quaternion *outOrientation)
{
  float fVar1;
  
  fVar1 = *(float *)(this + 0x7a0); // +0x7a0: current orientation quaternion w component
  if (fVar1 == 1.0f) { // Identity quaternion check (DAT_00e2b05c likely 1.0f)
    FUN_0045f5c0(outOrientation); // Sets quaternion to identity/zero
    *(float *)(this + 0x7a0) = *(float *)(outOrientation + 3); // Copy w from identity
    return;
  }
  // Copy quaternion components from vehicle state
  *(float *)(outOrientation + 0) = *(float *)(this + 0x100); // +0x100: quaternion x
  *(float *)(outOrientation + 4) = *(float *)(this + 0x104); // +0x104: quaternion y
  *(float *)(outOrientation + 8) = *(float *)(this + 0x108); // +0x108: quaternion z
  *(float *)(outOrientation + 12) = fVar1; // +0x7a0: quaternion w
  FUN_00471d20(outOrientation); // Normalize/validate quaternion
  return;
}