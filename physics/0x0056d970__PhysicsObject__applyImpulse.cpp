// FUNC_NAME: PhysicsObject::applyImpulse
void PhysicsObject::applyImpulse(int param_1)
{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *unaff_ESI; // pointer to impulse data (likely from a physics system)
  float local_30; // delta X
  float local_2c; // delta Y
  float local_28; // delta Z
  float local_24; // delta W (unused?)
  undefined1 local_20 [28]; // temporary buffer for matrix/transform

  // Get current world transform (likely from physics body)
  FUN_0056cba0(); // PhysicsSystem::getWorldTransform or similar
  local_30 = DAT_00e44564 - *unaff_ESI; // worldPos.x - impulseOrigin.x
  local_28 = DAT_00e44564 - unaff_ESI[2]; // worldPos.z - impulseOrigin.z
  local_2c = DAT_00e44564 - unaff_ESI[1]; // worldPos.y - impulseOrigin.y
  local_24 = unaff_ESI[3]; // impulseOrigin.w (unused?)

  // Get inverse transform or compute local impulse direction
  FUN_0056cba0(); // PhysicsSystem::getInverseTransform or similar
  pfVar1 = (float *)(param_1 + 0x10); // +0x10: linear velocity (vec3)
  FUN_0056cba0(local_20, &local_30, pfVar1); // Transform delta into local space

  // Apply impulse to linear velocity
  fVar2 = unaff_ESI[5]; // impulse.y
  fVar3 = unaff_ESI[6]; // impulse.z
  fVar4 = unaff_ESI[7]; // impulse.w (unused?)
  *pfVar1 = unaff_ESI[4] + *pfVar1; // impulse.x + velocity.x
  *(float *)(param_1 + 0x14) = fVar2 + *(float *)(param_1 + 0x14); // impulse.y + velocity.y
  *(float *)(param_1 + 0x18) = fVar3 + *(float *)(param_1 + 0x18); // impulse.z + velocity.z
  *(float *)(param_1 + 0x1c) = fVar4 + *(float *)(param_1 + 0x1c); // impulse.w + velocity.w (unused)
  *(undefined4 *)(param_1 + 0x1c) = 0; // Zero out the W component (likely unused)
  return;
}