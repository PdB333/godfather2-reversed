// FUNC_NAME: Entity::getVelocityMagnitude
float __fastcall Entity::getVelocityMagnitude(int thisPtr)
{
  int *vtablePtr;
  float *velocityPtr;
  float velX;
  float velY;
  float velZ;
  
  if ((*(int *)(thisPtr + 0x1e40) == 0) ||
     (vtablePtr = (int *)(*(int *)(thisPtr + 0x1e40) + -0x48), vtablePtr == (int *)0x0)) {
    // No physics body or invalid pointer - use default velocity from some global
    velocityPtr = (float *)FUN_005552b0();  // likely getDefaultVelocity or getZeroVector
    velX = *velocityPtr;
    velY = velocityPtr[1];
    velZ = velocityPtr[2];
  }
  else {
    // Call virtual function at vtable+0x4c to get velocity vector
    // This is likely getLinearVelocity or getVelocity
    (**(code **)(*vtablePtr + 0x4c))(&velX);
  }
  // Return magnitude of velocity vector: sqrt(x^2 + y^2 + z^2)
  return SQRT((float10)velY * (float10)velY +
              (float10)velX * (float10)velX + (float10)velZ * (float10)velZ);
}