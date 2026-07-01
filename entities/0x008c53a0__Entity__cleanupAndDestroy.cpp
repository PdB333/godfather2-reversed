// FUNC_NAME: Entity::cleanupAndDestroy
void __thiscall Entity::cleanupAndDestroy(int this, int entityData, int destroyType)
{
  int entityHandle;
  int slotIndex;
  
  entityHandle = FUN_008bee20(entityData); // Get entity handle from data
  if ((*(int *)(this + 0x54) == 0x637b907) && (destroyType == 1)) { // Check if entity type matches and destroy type is immediate
    FUN_008c48c0(entityHandle); // Immediate destroy callback
  }
  slotIndex = *(int *)(entityData + 0x88); // +0x88: slot count
  while (slotIndex = slotIndex + -1, -1 < slotIndex) {
    FUN_008c2e50(*(undefined4 *)(*(int *)(entityData + 0x84) + slotIndex * 4),entityData); // +0x84: slot array pointer
  }
  *(undefined4 *)(this + 0x154) = 0; // +0x154: clear some state flag
  slotIndex = FUN_008bdd00(entityHandle); // Get slot index from handle
  if (-1 < slotIndex) {
    FUN_008c2160(slotIndex); // Free slot at index
  }
  return;
}