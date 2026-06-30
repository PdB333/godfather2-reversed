// Xbox PDB: EARS::Modules::ConversationExchange::TryNPCConversation
// FUNC_NAME: NPCDialogManager::attemptConversation
void __thiscall NPCDialogManager::attemptConversation(int this, int npcA, int npcB)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  float fVar5;
  char local_46;
  byte local_45;
  char local_40 [64];
  
  // Check global game state (likely from GameManager)
  iVar2 = **(int **)(DAT_012233a0 + 4); // +0x4: some state pointer
  local_45 = 0;
  
  // Conditions to start conversation:
  // - Global state is 0 or 0x1f30 (menu/movie?), or bit 0x100 not set (not busy?)
  // - Conversation not already active (+0xe4 == 0)
  // - Both npcA and npcB valid
  // - Cooldown timer (currentTime - lastTime >= minInterval, and not negative)
  // - npcA is a valid conversation partner (FUN_006f6880)
  if ((((iVar2 == 0) || (iVar2 == 0x1f30)) || ((*(uint *)(iVar2 + 0x574) & 0x100) == 0)) &&
     (((*(int *)(this + 0xe4) == 0 && (npcA != 0)) &&
      ((npcB != 0 &&
       ((fVar5 = DAT_01205228 - *(float *)(this + 0xdc), // currentTime - lastConversationTime
        *(float *)(this + 0xe0) <= fVar5 && fVar5 != *(float *)(this + 0xe0) && // minInterval check
        (cVar1 = FUN_006f6880(npcA), cVar1 != '\0')))))))) {
    
    // Determine gender combination (M/F) based on bits at +0x1f54 (likely isMale flag)
    if ((*(byte *)(npcA + 0x1f54) & 1) == 0) { // npcA is male (bit0=0)
      cVar1 = 'M';
      local_46 = 'M';
      if ((*(byte *)(npcB + 0x1f54) & 1) == 0) { // npcB male
        iVar2 = *(int *)(this + 0xbc); // +0xbc: male-male conversation data pointer
      }
      else { // npcB female
        iVar2 = *(int *)(this + 0xc0); // +0xc0: male-female conversation data pointer
        cVar1 = 'F';
      }
    }
    else { // npcA is female (bit0=1)
      cVar1 = 'F';
      local_46 = 'F';
      if ((*(byte *)(npcB + 0x1f54) & 1) == 0) { // npcB male
        iVar2 = *(int *)(this + 0xc4); // +0xc4: female-male conversation data pointer
        cVar1 = 'M';
      }
      else { // npcB female
        iVar2 = *(int *)(this + 200); // +0xc8: female-female conversation data pointer
      }
    }
    
    if (iVar2 != 0) {
      FUN_00427180(); // Probably seed random or reset conversation state
      iVar2 = FUN_00b9a1c0(); // Returns an incremented conversation index (e.g., line number)
      
      // Build statement ID: "CONVERSATION_<gender1><gender2>_<index>_STATEMENT"
      _sprintf(local_40, "CONVERSATION_%c%c_%2.2d_STATEMENT", (int)local_46, (int)cVar1, iVar2 + 1);
      uVar3 = FUN_004dafd0(local_40); // Convert string to hash or ID
      *(undefined4 *)(this + 0xcc) = uVar3; // +0xcc: current statement ID
      
      // Build response ID: "CONVERSATION_<gender1><gender2>_<index>_RESPONSE"
      _sprintf(local_40, "CONVERSATION_%c%c_%2.2d_RESPONSE", (int)local_46, (int)cVar1, iVar2 + 1);
      uVar3 = FUN_004dafd0(local_40);
      *(undefined4 *)(this + 0xd0) = uVar3; // +0xd0: current response ID
      
      // Check both NPCs are still valid (alive, in range, etc.)
      iVar2 = FUN_006eafe0(npcA);
      iVar4 = FUN_006eafe0(npcB);
      
      if ((((iVar2 != 0) && (iVar4 != 0)) && 
           // Check statement and response strings exist
           (cVar1 = FUN_006f3b30(*(undefined4 *)(this + 0xcc)), cVar1 != '\0')) && 
          (cVar1 = FUN_006f3b30(*(undefined4 *)(this + 0xd0)), cVar1 != '\0')) {
        local_45 = 1; // Success flag
        
        // Trigger animations/sounds/states for both NPCs
        FUN_006ccd30(npcA); // Probably start conversation animation
        FUN_006ccd30(npcB);
        FUN_00732190(npcB); // Possibly set NPC state to "listening"
        FUN_00732190(npcA);
        FUN_007f6480(); // Queue something (maybe next line)
        FUN_007f6480();
        
        // Set flags
        *(byte *)(this + 0x8c) = *(byte *)(this + 0x8c) | 4; // +0x8c bit2: conversation started
        *(undefined4 *)(this + 0x78) = *(undefined4 *)(this + 0xd8); // +0x78: conversation duration (from +0xd8)
        *(undefined4 *)(this + 0xe4) = 1; // +0xe4: conversation active
        *(undefined4 *)(this + 0xe8) = 1; // +0xe8: some other flag
        FUN_00407e40(&DAT_012069c4); // Notify event manager / trigger callback
      }
    }
  }
  
  // Set the success flag bit (bit0 of +0x8c) to local_45
  *(byte *)(this + 0x8c) = *(byte *)(this + 0x8c) ^ (*(byte *)(this + 0x8c) ^ local_45) & 1;
  return;
}