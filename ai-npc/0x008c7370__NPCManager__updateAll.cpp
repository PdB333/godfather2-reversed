// FUNC_NAME: NPCManager::updateAll

void __thiscall NPCManager::updateAll(float timeDelta)
{
  uint i = 0;
  if (this->npcCount != 0) { // +0x34 = uint32 npcCount
    do {
      FUN_008c3ae0(timeDelta);
      i = i + 1;
    } while (i < this->npcCount);
  }
  return;
}