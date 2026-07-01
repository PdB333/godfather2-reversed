// FUNC_NAME: EntityManager::countEntitiesByTypeAndOwner
void __thiscall EntityManager::countEntitiesByTypeAndOwner(undefined4 this, int ownerId, short *outCount, short *outTotal)
{
  char cVar1;
  short sVar2;
  int entityPtr;
  short extraout_CX;
  undefined4 *iterator;
  int hasMore;
  int current;
  
  *outTotal = 0;
  *outCount = 0;
  FUN_004bab20(&iterator, this, ownerId); // likely getEntityIterator or begin
LAB_008a62a0:
  do {
    if ((hasMore == 0) && (current == 0)) {
      return;
    }
    entityPtr = (*(code *)*iterator)(); // iterator->next()
    if ((*(int *)(entityPtr + 8) == DAT_00e54408) && (*(int *)(entityPtr + 0x10) == ownerId)) {
      sVar2 = FUN_008a6ea0(entityPtr); // isEntityAlive?
      if (sVar2 != 0) {
        cVar1 = FUN_008a5c90(entityPtr); // isEntitySpecial?
        if (cVar1 != '\0') {
          *outCount = *outCount + extraout_CX;
          (*(code *)iterator[2])(); // iterator->advance()
          goto LAB_008a62a0;
        }
        *outTotal = *outTotal + extraout_CX;
      }
    }
    (*(code *)iterator[2])(); // iterator->advance()
  } while( true );
}