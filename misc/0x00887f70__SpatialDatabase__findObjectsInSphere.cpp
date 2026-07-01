// FUNC_NAME: SpatialDatabase::findObjectsInSphere
void __thiscall SpatialDatabase::findObjectsInSphere(int this, int outputArray, float *sphereCenter)
{
  int objectCount;
  int objectIndex;
  uint currentIndex;
  float dx;
  float dy;
  float dz;
  float distSq;
  
  objectCount = *(int *)(this + 0x80) - *(int *)(this + 0x7c);
  // Signed division by 0x50 (80 bytes per object entry)
  objectIndex = objectCount >> 0x1f;
  currentIndex = 0;
  if (objectCount / 0x50 + objectIndex != objectIndex) {
    objectIndex = 0;
    do {
      // Get object pointer from spatial grid cell
      int objectPtr = *(int *)(objectIndex + 0x14 + *(int *)(this + 0x7c));
      // Calculate squared distance between sphere center and object position (offset +0x14, +0x18, +0x1c)
      dx = *(float *)(objectPtr + 0x14) - *sphereCenter;
      dy = *(float *)(objectPtr + 0x18) - sphereCenter[1];
      dz = *(float *)(objectPtr + 0x1c) - sphereCenter[2];
      distSq = dx * dx + dy * dy + dz * dz;
      // Compare with squared sphere radius (object at +0x20)
      if (distSq < *(float *)(objectPtr + 0x20) * *(float *)(objectPtr + 0x20) &&
          // Check if output array has room (capacity at +0x80)
          *(uint *)(outputArray + 0x80) < 0x20) {
        // Store object pointer in output array
        *(int *)(outputArray + *(uint *)(outputArray + 0x80) * 4) = objectPtr;
        *(int *)(outputArray + 0x80) = *(int *)(outputArray + 0x80) + 1;
      }
      currentIndex++;
      objectIndex += 0x50; // Each cell entry is 80 bytes
    } while (currentIndex < (uint)((*(int *)(this + 0x80) - *(int *)(this + 0x7c)) / 0x50));
  }
  return;
}