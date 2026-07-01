// FUNC_NAME: EntityManager::removeEntity
// Address: 0x0097de20
// Removes an entity ID from the active list. If the sum of all counters becomes zero, triggers shutdown.

void __thiscall EntityManager::removeEntity(int entityId)
{
  uint count = this->m_entityCount; // +0x30
  uint i = 0;

  if (count != 0)
  {
    int* array = reinterpret_cast<int*>(this + 0x10); // array of entity IDs
    while (array[i] != entityId)
    {
      i++;
      if (count <= i)
      {
        return; // entity not found
      }
    }

    if (static_cast<int>(i) >= 0)
    {
      count--;
      this->m_entityCount = count; // +0x30
      if (i != count)
      {
        // Move the last element into the removed slot
        array[i] = array[count];
      }

      // Check if all managed counters are empty
      if (this->m_counterA + this->m_counterB + this->m_counterC + this->m_entityCount == 0)
      {
        // +0x9c, +0x78, +0x54
        FUN_0097c5d0(); // shutdown or cleanup
      }
    }
  }
}