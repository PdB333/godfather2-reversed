// FUNC_NAME: SomeClass::checkDistanceAndTrigger
void SomeClass::checkDistanceAndTrigger(float *targetPos)
{
  float *pfVar1;
  int in_EAX;
  int unaff_FS_OFFSET;
  float fVar2;
  
  // Get some object's position from a global/thread-local structure
  // +0x2c: FS segment offset (thread-local storage)
  // +0x08: offset within that structure
  // +0x80: offset to position data
  // +0x10: offset from this pointer (in_EAX) to some index
  pfVar1 = (float *)(*(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + 0x80 +
                    *(int *)(in_EAX + 0x10));
  
  // Calculate squared distance between targetPos and the object's position
  fVar2 = (targetPos[1] - pfVar1[1]) * (targetPos[1] - pfVar1[1]) +
          (*targetPos - *pfVar1) * (*targetPos - *pfVar1) +
          (targetPos[2] - pfVar1[2]) * (targetPos[2] - pfVar1[2]);
  
  // Check if distance is within range [minSq, maxSq)
  // +0x30: minimum squared distance threshold
  // +0x34: maximum squared distance threshold
  if ((*(float *)(in_EAX + 0x30) <= fVar2) && (fVar2 < *(float *)(in_EAX + 0x34))) {
    FUN_004f8980(); // Trigger some action
    return;
  }
  return;
}