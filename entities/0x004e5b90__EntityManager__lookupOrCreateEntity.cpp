// FUNC_NAME: EntityManager::lookupOrCreateEntity
void EntityManager::lookupOrCreateEntity(uint entityId, undefined4 *entityData)
{
  uint *hashEntry;
  uint entityIndex;
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  hashEntry = *(uint **)(*(int *)(*(int *)(DAT_01223398 + 8) + 4) +
                     (entityId % *(uint *)(*(int *)(DAT_01223398 + 8) + 8)) * 4);
  do {
    if (hashEntry == (uint *)0x0) {
LAB_004e5bc3:
      entityIndex = 0;
LAB_004e5bc5:
      uVar1 = entityData[5];
      uVar2 = entityData[6];
      uVar3 = entityData[7];
      *(undefined4 *)(entityIndex + 0x30) = entityData[4];
      *(undefined4 *)(entityIndex + 0x34) = uVar1;
      *(undefined4 *)(entityIndex + 0x38) = uVar2;
      *(undefined4 *)(entityIndex + 0x3c) = uVar3;
      uVar1 = entityData[1];
      uVar2 = entityData[2];
      uVar3 = entityData[3];
      *(undefined4 *)(entityIndex + 0x70) = *entityData;
      *(undefined4 *)(entityIndex + 0x74) = uVar1;
      *(undefined4 *)(entityIndex + 0x78) = uVar2;
      *(undefined4 *)(entityIndex + 0x7c) = uVar3;
      *(undefined4 *)(entityIndex + 0x8c) = entityData[9];
      *(undefined4 *)(entityIndex + 0x88) = entityData[8];
      uVar1 = entityData[10];
      *(undefined1 *)(entityIndex + 0x98) = 1;
      *(undefined4 *)(entityIndex + 0x84) = uVar1;
      return;
    }
    if (*hashEntry == entityId) {
      if ((hashEntry != (uint *)0x0) && (hashEntry + 1 != (uint *)0x0)) {
        entityIndex = hashEntry[1];
        goto LAB_004e5bc5;
      }
      goto LAB_004e5bc3;
    }
    hashEntry = (uint *)hashEntry[2];
  } while( true );
}