// FUNC_NAME: Entity::getComponentByType
uint __thiscall Entity::getComponentByType(int this, uint componentType)
{
  if (componentType != 0) {
    componentType = FUN_00849a70(componentType); // likely hashComponentType or lookupComponentType
    if ((-1 < (int)componentType) &&
       (componentType = *(uint *)(*(int *)(this + 0x10) + componentType * 4), componentType != 0)) {
      // +0x10: pointer to component array (array of pointers)
      // +0x58: component flags/status byte, bitwise NOT and mask to clear low byte
      return CONCAT31((int3)(componentType >> 8),~*(byte *)(componentType + 0x58)) & 0xffffff01;
    }
  }
  // Return with low byte cleared (invalid/not found)
  return componentType & 0xffffff00;
}