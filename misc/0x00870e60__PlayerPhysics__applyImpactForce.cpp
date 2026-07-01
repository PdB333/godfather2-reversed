// FUNC_NAME: PlayerPhysics::applyImpactForce
void __thiscall PlayerPhysics::applyImpactForce(int thisPtr, int impactSource, float knockbackStrength, float minDistance)
{
  int physicsManager = FUN_00471610();
  float dx = *(float *)(thisPtr + 0x60) - *(float *)(physicsManager + 0x30);  // +0x60 = worldPos.x, +0x30 = playerPos.x
  float dy = *(float *)(thisPtr + 100) - *(float *)(physicsManager + 0x34);  // +100 = worldPos.y, +0x34 = playerPos.y (offsets are 100 = 0x64? Actually 100 decimal = 0x64)
  float dz = *(float *)(thisPtr + 0x68) - *(float *)(physicsManager + 0x38); // +0x68 = worldPos.z, +0x38 = playerPos.z
  
  float distSq = dx * dx + dy * dy + dz * dz;
  
  // Initialize direction vector
  Vector3 direction;
  direction.x = dx;
  direction.y = dy;
  direction.z = dz;
  
  int zero = 0;
  
  // Normalize the direction vector
  FUN_0056afa0(&direction, &direction);
  
  // Scale by knockback strength
  dx = direction.x * knockbackStrength;
  dy = direction.y * knockbackStrength;
  dz = direction.z * knockbackStrength;
  
  // Check if current distance is within the knockback minimum distance
  if (distSq <= (dz * dz + dx * dx + dy * dy) * minDistance * minDistance) {
    // Recalculate raw vector if too far - this applies falloff at distances beyond minDistance
    dx = *(float *)(thisPtr + 0x60) - *(float *)(physicsManager + 0x30);
    dy = *(float *)(thisPtr + 100) - *(float *)(physicsManager + 0x34);
    dz = *(float *)(thisPtr + 0x68) - *(float *)(physicsManager + 0x38);
  }
  
  // Apply velocity or force (possibly setting velocity with zero y component for ground-only impact)
  FUN_0046fe50(&dx, 0);  // Sets velocity, second param might be flags (0 = apply to all axes)
  FUN_005466c0(&dx);     // Additional physics update
}