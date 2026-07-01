// FUNC_NAME: NPCManager::updateDespawnQueue
void __thiscall NPCManager::updateDespawnQueue(int this, undefined4 param_2)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (*(int *)(this + 0x34) != 0) {
    do {
      iVar1 = *(int *)(*(int *)(this + 0x30) + uVar3 * 4);
      uVar2 = *(uint *)(iVar1 + 0x84); // NPC flags at +0x84
      // Check: not flagged for despawn (bit 5 clear), not already despawning (bit 4 clear),
      // and either not flagged for immediate despawn (bit 6 clear) or
      // (NPC type is not a specific gangster type OR bit 9 is set)
      if ((((~(byte)(uVar2 >> 5) & 1) != 0) && ((uVar2 >> 4 & 1) == 0)) &&
         (((~(byte)(uVar2 >> 6) & 1) != 0 ||
          ((*(int *)(iVar1 + 0x54) != -0x50e6cf8b || ((uVar2 >> 9 & 1) != 0)))))) {
        FUN_008c3b40(param_2); // Despawn the NPC
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(this + 0x34));
  }
  return;
}