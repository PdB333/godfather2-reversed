// FUNC_NAME: NPCManager::canNPCBeAssignedToJob
undefined4 __thiscall NPCManager::canNPCBeAssignedToJob(int thisPtr, int npcData)
{
  char cVar1;
  
  if ((((*(int *)(npcData + 0x40) == *(int *)(thisPtr + 4)) ||       // +0x40: npcFamilyId, +0x04: playerFamilyId
       ((*(int *)(npcData + 0x40) != *(int *)(thisPtr + 8) &&        // +0x08: enemyFamilyId
        (*(int *)(thisPtr + 4) == 0)))) &&                            // playerFamilyId == 0 (neutral)
      (cVar1 = FUN_006b81b0(*(undefined4 *)(npcData + 0x48)),        // +0x48: npcRole check
       cVar1 != '\0')) &&
     ((*(uint *)(thisPtr + 0x1c) <= *(uint *)(npcData + 0x50) &&     // +0x1c: minLevel, +0x50: npcLevel
      (((*(uint *)(thisPtr + 0x20) == 0 ||                           // +0x20: allowedRoles bitmask
        ((*(uint *)(thisPtr + 0x20) & 1 << ((byte)*(undefined4 *)(npcData + 0xc4) & 0x1f)) != 0)) &&  // +0xc4: npcRoleIndex
       (cVar1 = FUN_006b7f60(*(undefined4 *)(npcData + 0x34)),       // +0x34: npcAvailability check
        cVar1 != '\0')))))) {
    cVar1 = FUN_006b7fd0(*(undefined4 *)(npcData + 0xd4));           // +0xd4: npcJobAssignment check
    if (cVar1 != '\0') {
      return 1;
    }
  }
  return 0;
}