// FUNC_NAME: SomeClass::checkAllEntitiesValid
char SomeClass::checkAllEntitiesValid(int param_1)
{
  int *piVar1;
  int *piVar2;
  char cVar3;
  uint uVar4;
  
  piVar1 = *(int **)(param_1 + 0x14);  // +0x14: pointer to entity list container
  uVar4 = 0;
  cVar3 = '\0';
  if (piVar1[1] != 0) {  // piVar1[1] = count of entities
    do {
      if (cVar3 != '\0') {
        return cVar3;
      }
      param_1 = *(undefined4 *)(*piVar1 + uVar4 * 4);  // get entity pointer from list
      piVar2 = (int *)FUN_004986e0(&param_1);  // likely getEntityData or similar
      if ((*piVar2 == 0) || (*(int *)(*piVar2 + 0x28) != 1)) {  // +0x28: some state/type field, 1 = valid
        cVar3 = '\x01';  // mark as invalid
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < (uint)piVar1[1]);
  }
  return cVar3;
}