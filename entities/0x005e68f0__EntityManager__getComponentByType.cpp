// FUNC_NAME: EntityManager::getComponentByType
int EntityManager::getComponentByType(void)
{
  int componentArray;
  int componentPtr;
  uint componentType;
  uint entityId;
  
  entityId = unaff_ESI & 0xffff;
  if (entityId < 0x200) {
    componentArray = entityId * 0x30 + 0x10 + DAT_012234bc; // +0x10: component array offset in entity manager
    if (((((componentArray != 0) && (*(uint *)(componentArray + 0x2c) == unaff_ESI)) && (componentArray != 0)) &&
        ((((*(int *)(componentArray + 0x10) != 0 &&
           (componentArray = *(int *)(*(int *)(componentArray + 0x10) + 8), componentArray != 0)) &&
          ((entityId < 0x200 &&
           ((componentPtr = entityId * 0x30 + 0x10 + DAT_012234bc, componentPtr != 0 &&
            (*(uint *)(componentPtr + 0x2c) == unaff_ESI)))))) && (componentPtr != 0)))) &&
       (((*(int **)(componentPtr + 0x10) != (int *)0x0 && (componentPtr = **(int **)(componentPtr + 0x10), componentPtr != 0))
        && (componentType = (uint)*(byte *)(componentArray + 0x66), componentType != 0xff)))) {
      return *(int *)(componentPtr + 0x50) + componentType * 8; // +0x50: component type table offset
    }
  }
  return 0;
}