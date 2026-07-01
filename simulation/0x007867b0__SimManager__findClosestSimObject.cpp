// FUNC_NAME: SimManager::findClosestSimObject
int __thiscall SimManager::findClosestSimObject(float *targetPos, char filterEnabled)
{
  int foundObject = 0;
  unsigned int index = 0;

  // +0x1a3c: count of sim objects in list
  if (this->simObjectCount != 0)
  {
    // +0x193c: pointer to array of SimObject pointers
    SimObject **objectList = (SimObject **)((char *)this + 0x193c);
    while (true)
    {
      foundObject = (int)objectList[index];

      // If filtering is requested, call isTargetable; skip if it fails
      // FUN_007883e0 likely returns 0 if not targetable
      if (filterEnabled != '\0' && !isTargetable((SimObject *)foundObject))
      {
        // continue to next object
      }
      else
      {
        // Compute squared distance (object position at +0x10, +0x14, +0x18)
        float dx = *(float *)(foundObject + 0x10) - targetPos[0];
        float dy = *(float *)(foundObject + 0x14) - targetPos[1];
        float dz = *(float *)(foundObject + 0x18) - targetPos[2];
        float distSq = dx * dx + dy * dy + dz * dz;

        // Global threshold (DAT_00d5f6f0)
        if (distSq < g_maxTargetDistanceSq)
        {
          break; // found a valid object within range
        }
      }

      index++;
      if (index >= this->simObjectCount)
      {
        return 0; // no object found
      }
    }
  }
  return foundObject;
}