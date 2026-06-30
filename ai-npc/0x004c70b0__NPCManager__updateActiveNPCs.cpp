// FUNC_NAME: NPCManager::updateActiveNPCs
void NPCManager::updateActiveNPCs(void)
{
  int iVar1;
  uint uVar2;
  int *this; // unaff_ESI
  int iVar3;
  
  // Check if NPC manager is in correct state and has active NPCs
  if ((*this != 2) && (uVar2 = 0, this[0x28] != 0)) { // this[0x28] = activeNPC count
    iVar3 = 0;
    do {
      // Check NPC flags at offset 0xB2 for bit 0 (active flag)
      // Check NPC state at offset 0x04 (must be 1 = alive)
      // Check NPC state at offset 0x06 (must be non-zero = valid)
      // Check NPC flags at offset 0x08 (bit 4 = not dead)
      if (((((*(byte *)(*(int *)(this[0x29] + iVar3) + 0xb2) & 1) != 0) && // +0xB2: active flag
           (iVar1 = *(int *)(this[0x29] + iVar3 + 4), *(char *)(iVar1 + 4) == '\x01')) && // +0x04: state = alive
          (*(char *)(iVar1 + 6) != '\0')) && // +0x06: valid flag
         ((*(byte *)(iVar1 + 8) & 0x10) == 0)) { // +0x08: not dead flag
        FUN_00459b30(iVar1,0); // Call NPC update function with parameter 0
      }
      uVar2 = uVar2 + 1;
      iVar3 = iVar3 + 0x1c; // Each NPC entry is 0x1C bytes
    } while (uVar2 < (uint)this[0x28]); // Loop through all active NPCs
  }
  return;
}