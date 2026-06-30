// FUNC_NAME: Vehicle::applySteeringImpulse
void __thiscall Vehicle::applySteeringImpulse(int this, undefined4 param_2) {
  int iVar1;
  int unaff_FS_OFFSET; // likely __security_cookie or TLS reference
  float fVar2;
  float fVar3;
  undefined1 local_50 [76];

  // Likely convert/validate input, maybe set up physics context
  FUN_00423860(param_2); // e.g., PhysicsWorld::lock or similar
  FUN_00417560();        // e.g., PhysicsWorld::sync or update

  // Get steering angle (or target angle) from the vehicle data at +0x8c
  // +0x4 -> VehicleData* (base vehicle properties)
  // +0x10 -> wheel array base? +0x30 offset per wheel entry, 0x24 stride
  // +0xe -> current wheel index (short)
  fVar3 = *(float *)(*(int *)(this + 4) + 0x8c); // m_steeringAngle from VehicleData+0x8c

  iVar1 = *(int *)(*(int *)(this + 4) + 0x10) + 0x30 + *(short *)(this + 0xe) * 0x24;
  // iVar1 points to current wheel data: struct WheelEntry { float something; ... }
  // +0x14 (float) -> steering multiplier? +0x18 (float) -> current wheel angle
  // +0x1c (float) -> another multiplier? +0x20 (float) -> another angle

  fVar2 = (fVar3 - *(float *)(iVar1 + 0x18)) * *(float *)(iVar1 + 0x14);
  if (0.0 < fVar2) {
    if (DAT_00e2b1a4 <= fVar2) { // DAT_00e2b1a4 = maxSteeringClamp (float)
      fVar2 = DAT_00e2b1a4;
    }
  }
  else {
    fVar2 = 0.0;
  }

  fVar3 = (fVar3 - *(float *)(iVar1 + 0x20)) * *(float *)(iVar1 + 0x1c);
  if (0.0 < fVar3) {
    if (DAT_00e2b1a4 <= fVar3) {
      fVar3 = DAT_00e2b1a4;
    }
  }
  else {
    fVar3 = 0.0;
  }

  // Call physics apply steering torque via vtable
  // this+0x28 -> some interface pointer (e.g., IPhysicsBody*)
  // (**(code **)(**(int **)(this + 0x28) + 8)) -> vtable[2] = applyTorque or applyForce
  // unaff_FS_OFFSET+0x2c -> likely some per-thread context
  // *(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + 0x50 + *(int *)(this + 0x10) -> target/body pointer
  // last arg = fVar3 * fVar2 = combined steering impulse magnitude
  (**(code **)(**(int **)(this + 0x28) + 8))
            (param_2,
             *(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + 0x50 + *(int *)(this + 0x10),
             local_50,
             *(undefined4 *)(this + 0x24),
             this + 0x30,
             fVar3 * fVar2);
  return;
}