// FUNC_NAME: NPCManager::updateNPCs
void __fastcall NPCManager::updateNPCs(int this)
{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  undefined4 local_14;
  undefined4 local_10;
  undefined1 local_c [12];
  
  FUN_0083e300(local_c,&local_10,&local_14); // Get some context data (likely player position or time)
  uVar6 = 0;
  if (*(int *)(this + 0x78) != 0) { // +0x78: NPC count
    do {
      iVar4 = *(int *)(*(int *)(this + 0x74) + uVar6 * 8); // +0x74: NPC array pointer, each entry 8 bytes
      if ((iVar4 != 0) && (iVar1 = iVar4 + -0x48, iVar1 != 0)) { // -0x48: offset to NPC base object
        if ((*(uint *)(iVar4 + 0x1f10) >> 0x19 & 1) == 0) { // +0x1f10: flags, bit 25 = some state flag
          iVar3 = FUN_00806440(); // Get game state (e.g., paused, menu open)
          if ((iVar3 == 3) || (iVar3 == 2)) { // Game state 2 or 3 (e.g., in menu or cutscene)
            if (*(int *)(iVar4 + 0x110) == 0) { // +0x110: pointer to some behavior/state machine
              *(undefined1 **)(iVar4 + 0x110) = &LAB_006bcba0; // Set default behavior
            }
          }
          else {
            cVar2 = FUN_0083c4c0(iVar1,local_c,local_10,local_14); // Check if NPC should be updated (e.g., in range)
            if (cVar2 != '\0') goto LAB_006bd0ad; // Skip update if not in range
          }
          iVar4 = FUN_007351c0(); // Get player controller
          if ((((*(byte *)(iVar4 + 0x5f) & 1) == 0) || // +0x5f: player flags, bit 0 = some state
              (piVar5 = (int *)FUN_0043b870(DAT_01131040), piVar5 == (int *)0x0)) || // Get some global object
             (cVar2 = (**(code **)(*piVar5 + 0x1c))(0x100), cVar2 == '\0')) { // Check if player is in certain state
            FUN_0083f190(iVar1); // Update NPC AI/behavior
          }
        }
        else {
LAB_006bd0ad:
          FUN_004088c0(iVar4 + -0xc); // Remove/destroy NPC (e.g., out of range or dead)
        }
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(this + 0x78));
  }
  FUN_006bccd0(); // Post-update cleanup (e.g., remove dead NPCs from list)
  return;
}