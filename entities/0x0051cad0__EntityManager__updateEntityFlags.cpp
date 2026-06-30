// FUNC_NAME: EntityManager::updateEntityFlags
void EntityManager::updateEntityFlags(void)
{
  int *pNextEntity;
  int entityIndex;
  int currentEntity; // unaff_ESI
  int entityListHead; // iVar3

  entityListHead = DAT_01205514; // Global entity list head pointer
  if (DAT_01205514 != 0) {
    do {
      if (currentEntity == 0) {
LAB_0051caf9:
        // Set flag 0x100000 on entity at +0x0C (flags field)
        *(uint *)(entityListHead + 0xc) = *(uint *)(entityListHead + 0xc) | 0x100000;
        FUN_0051b120(); // Likely EntityManager::processFlaggedEntities
      }
      else {
        // Check entity at +0xC4 (some kind of parent/owner pointer)
        if (*(int *)(entityListHead + 0xc4) == 0) {
          entityIndex = 0;
        }
        else {
          entityIndex = *(int *)(entityListHead + 0xc4) + -0x48; // Offset to get index
        }
        if (currentEntity == entityIndex) goto LAB_0051caf9;
      }
      pNextEntity = (int *)(entityListHead + 0x14); // +0x14 = next entity pointer
      entityListHead = *pNextEntity;
    } while (*pNextEntity != 0);
  }
  return;
}