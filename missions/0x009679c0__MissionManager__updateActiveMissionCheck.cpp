// FUNC_NAME: MissionManager::updateActiveMissionCheck
void __fastcall MissionManager::updateActiveMissionCheck(int thisPtr)
{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  iVar4 = DAT_01129930; // global mission manager instance
  puVar1 = (uint *)(DAT_01129930 + 0x2b4); // +0x2B4: current mission index
  uVar6 = 0;
  *(undefined4 *)(DAT_01129930 + 0x2b8) = 0; // +0x2B8: some mission state counter
  
  // Check if current mission index is valid, mission data exists, and mission is active
  if (((*puVar1 < *(uint *)(DAT_0112b9b4 + 0x2c)) && (DAT_011308b6 != '\0')) &&
     (iVar2 = *(int *)(*(int *)(DAT_0112b9b4 + 0x28) + *puVar1 * 4), *(int *)(thisPtr + 0x14) != 0))
  {
    do {
      // Check if mission type matches (using lookup table at 0xD8DCA8)
      if (*(int *)(&DAT_00d8dca8 + (uint)(byte)(&DAT_011308a0)[uVar6 + DAT_011308b7] * 0x10) ==
          *(int *)(iVar2 + 0x20)) {
        uVar3 = *(uint *)(&DAT_00d8dcac + (uint)(byte)(&DAT_011308a0)[uVar6 + DAT_011308b7] * 0x10);
        iVar5 = *(int *)(iVar4 + 0x2b8) * 0x10;
        
        // Check if this mission is better than current best match
        if (((*(int *)(&DAT_00d8dca8 + iVar5) !=
              *(int *)(&DAT_00d8dca8 + (uint)(byte)(&DAT_011308a0)[uVar6 + DAT_011308b7] * 0x10)) ||
            ((*(uint *)(&DAT_00d8dcac + iVar5) < uVar3 && (uVar3 <= *(uint *)(iVar2 + 0x3c))))) &&
           (*(uint *)(iVar4 + 0x2b8) = uVar6, uVar3 == *(uint *)(iVar2 + 0x3c))) {
          return; // Found best match, exit
        }
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(thisPtr + 0x14)); // Loop through all mission slots
  }
  return;
}