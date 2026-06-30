// FUNC_NAME: EntityManager::releaseDeadEntities
void EntityManager::releaseDeadEntities(int param_1, int param_2, int param_3)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  // Iterate over all categories in the entity list
  iVar3 = *(int *)(param_1 + 4);
  if (iVar3 != *(int *)(param_1 + 0xc)) {
    do {
      // Iterate over entities within this category
      piVar4 = *(int **)(iVar3 + 0x20);
      if (*(int **)(iVar3 + 0x20) != *(int **)(iVar3 + 0x28)) {
        do {
          piVar1 = (int *)piVar4[0x10];
          
          // Check if entity's type matches param_2 (category ID)
          // +0x49 stores type info, -4 adjusts for the type field offset
          if (piVar4[0x49] == 0) {
            iVar2 = 0;
          }
          else {
            iVar2 = piVar4[0x49] + -4;
          }
          
          // If type matches and entity has script data (+0x34) and is not active
          if (((iVar2 == param_2) && (piVar4[0x34] != 0)) &&
             (FUN_0066df80(*(undefined4 *)(param_3 + 0xa0)), *(int *)(piVar4[0x34] + 0x10) == 0)) {
            // Release the entity: clear script data, remove from linked list
            FUN_0066dfe0();
            piVar4[0x34] = 0;
            
            // Remove from doubly-linked list (entity chain)
            *(int *)(piVar4[0x11] + 0x40) = piVar4[0x10];
            *(int *)(piVar4[0x10] + 0x44) = piVar4[0x11];
            
            // Call destructor/release method on entity
            (**(code **)(*piVar4 + 4))();
            
            // Add to free list at param_1 + 0x37c08
            piVar4[0x10] = *(int *)(param_1 + 0x37c08);
            *(int **)(param_1 + 0x37c08) = piVar4;
          }
          
          piVar4 = piVar1;
        } while (piVar1 != *(int **)(iVar3 + 0x28));
      }
      
      iVar3 = *(int *)(iVar3 + 0x2c);
    } while (iVar3 != *(int *)(param_1 + 0xc));
  }
  return;
}