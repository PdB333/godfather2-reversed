// FUNC_NAME: Entity::getSpeed
float __fastcall Entity::getSpeed(int thisPtr)
{
  int *vtablePtr;
  float result;
  float velocityX;
  float velocityY;
  float velocityZ;
  
  velocityX = 0.0f;
  if ((*(int *)(thisPtr + 0x70) != 0) &&
     (vtablePtr = (int *)(*(int *)(thisPtr + 0x70) + -0x48), vtablePtr != (int *)0x0)) {
    // Check if we have a cached speed value (bit 0 of +0xC9)
    if ((*(byte *)(thisPtr + 0xc9) & 1) != 0) {
      // Return cached speed from virtual function at vtable+0x1B0
      result = (float)(**(code **)(*vtablePtr + 0x1b0))();
      return result;
    }
    // Get velocity vector from virtual function at vtable+0x4C
    if (*(int *)(thisPtr + 0x70) == 0) {
      vtablePtr = (int *)0x0;
    }
    else {
      vtablePtr = (int *)(*(int *)(thisPtr + 0x70) + -0x48);
    }
    (**(code **)(*vtablePtr + 0x4c))(&velocityX);
    // Calculate speed as magnitude of velocity vector
    velocityX = SQRT(velocityZ * velocityZ + velocityX * velocityX + velocityY * velocityY);
  }
  return (float)velocityX;
}