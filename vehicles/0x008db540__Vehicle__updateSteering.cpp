// FUNC_NAME: Vehicle::updateSteering
void __fastcall Vehicle::updateSteering(int this)
{
  float fVar1;
  float fVar2;
  undefined4 unaff_retaddr;
  
  // Call virtual function at vtable+0x28 (likely getSteeringInput or similar)
  (**(code **)(*(int *)(this + 0x58) + 0x28))(0x10);
  *(undefined4 *)(this + 400) = unaff_retaddr;
  
  // Two calls to unknown function (likely math or clamping)
  FUN_004df600();
  FUN_004df600();
  
  fVar2 = *(float *)(this + 0x1c8); // +0x1C8: speed or velocity factor
  if (*(int *)(this + 400) != 0) {
    fVar2 = *(float *)(*(int *)(this + 400) + 0x1db8) * fVar2; // +0x1DB8: steering multiplier from some object
  }
  
  fVar1 = (float)DAT_01205224; // Global steering constant
  if (DAT_01205224 < 0) {
    fVar1 = fVar1 + DAT_00e44578; // Another global constant
  }
  
  *(float *)(this + 0x1ac) = fVar1 + fVar2 * DAT_00d60d04; // +0x1AC: steering angle or turn rate
  return;
}