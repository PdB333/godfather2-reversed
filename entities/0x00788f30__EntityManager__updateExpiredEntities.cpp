// FUNC_NAME: EntityManager::updateExpiredEntities
void __thiscall EntityManager::updateExpiredEntities(int *this, float currentTime)
{
  float fVar1;
  int *nextEntity;
  bool bVar3;
  int iVar4;
  
  this = (int *)*this; // dereference to get head of linked list
  bVar3 = false;
  if (this != (int *)0x0) {
    do {
      fVar1 = (float)this[2]; // +0x08: expirationDuration
      nextEntity = (int *)*this; // +0x00: next pointer in linked list
      iVar4 = FUN_007856f0(this[1]); // +0x04: entity ID -> get entity object
      if (*(float *)(iVar4 + 0x14) + fVar1 < currentTime) { // entity->creationTime + expirationDuration < currentTime
        FUN_00788b40(this); // remove entity from list
        if (this[6] != 0) { // +0x18: some flag or pointer
          FUN_004daf90(this + 6); // release/cleanup
        }
        (**(code **)(*(int *)(DAT_0112aa1c + 0x2c40) + 4))(this,0); // delete entity
        bVar3 = true;
      }
      this = nextEntity;
    } while (nextEntity != (int *)0x0);
    if (bVar3) {
      FUN_00788720(); // update entity manager state after removals
    }
  }
  return;
}