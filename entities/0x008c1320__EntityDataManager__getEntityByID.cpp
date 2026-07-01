// FUNC_NAME: EntityDataManager::getEntityByID
undefined4 __thiscall EntityDataManager::getEntityByID(int this, undefined4 entityID)
{
  int index;
  
  index = this->getIndexFromID(entityID);  // Convert entity ID to internal index
  if (index >= 0) {
    // Return pointer from array at offset +0x1A4 (m_pEntityArray)
    return *(undefined4 *)(*(int *)(this + 0x1A4) + index * 4);
  }
  return 0;  // Invalid ID or not found
}