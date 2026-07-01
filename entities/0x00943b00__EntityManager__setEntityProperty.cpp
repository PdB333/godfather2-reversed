// FUNC_NAME: EntityManager::setEntityProperty
void __thiscall EntityManager::setEntityProperty(int entityId, int value)
{
  // Look up index from entity ID
  int index = FUN_00941490(&entityId);
  if (index < 0)
    return;

  // Manager stores an array of 8-byte slots at +0xf0.
  // Layout: [count (4)] [slot0] [slot1] ... each slot: [entityPtr (4)] [??? (4)].
  int *slotPtr = *(int **)(this + 0xF0) + 4 + index * 8;
  if (slotPtr == nullptr)
    return;

  // First 4 bytes of slot: pointer to entity
  int *entityPtr = *slotPtr;
  if (entityPtr == nullptr)
    return;

  // Entity has a pointer to a component at +0x0C.
  // Write the value into component's field at +0x2C.
  int *componentPtr = *(int **)(entityPtr + 0x0C);
  *(int *)(componentPtr + 0x2C / 4) = value;
}