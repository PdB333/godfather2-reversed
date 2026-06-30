// FUNC_NAME: EntityManager::findOrCreateEntity
void EntityManager::findOrCreateEntity(uint entityId, undefined4 *entityData)
{
  uint *hashBucket;
  uint entityPtr;
  undefined4 data1;
  undefined4 data2;
  undefined4 data3;
  undefined4 data4;
  
  hashBucket = *(uint **)(*(int *)(*(int *)(DAT_01223398 + 8) + 4) +
                     (entityId % *(uint *)(*(int *)(DAT_01223398 + 8) + 8)) * 4);
  do {
    if (hashBucket == (uint *)0x0) {
LAB_004e5923:
      entityPtr = 0;
LAB_004e5925:
      data1 = entityData[1];  // +0x04
      data2 = entityData[2];  // +0x08
      data3 = entityData[3];  // +0x0C
      *(undefined4 *)(entityPtr + 0x30) = *entityData;  // entity +0x30 = first field
      *(undefined4 *)(entityPtr + 0x34) = data1;
      *(undefined4 *)(entityPtr + 0x38) = data2;
      *(undefined4 *)(entityPtr + 0x3c) = data3;
      *(undefined1 *)(entityPtr + 0x98) = 1;  // +0x98 = active flag (bool)
      return;
    }
    if (*hashBucket == entityId) {
      if ((hashBucket != (uint *)0x0) && (hashBucket + 1 != (uint *)0x0)) {
        entityPtr = hashBucket[1];  // hashBucket[1] = entity pointer
        goto LAB_004e5925;
      }
      goto LAB_004e5923;
    }
    hashBucket = (uint *)hashBucket[2];  // hashBucket[2] = next in chain
  } while( true );
}