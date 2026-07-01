// FUNC_NAME: LobbyManager::updateLobbyState

undefined4 __fastcall LobbyManager::updateLobbyState(int this)
{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  undefined8 uVar6;
  undefined8 uStack_8;
  
  uVar4 = 0;
  // Check if lobby timer is active and countdown has expired
  if ((DAT_011308e8 != 0) && (DAT_00d5779c < DAT_01205228 - _DAT_011308e4)) {
    // Set lobby timeout flag
    *(uint *)(this + 0x6f4) = *(uint *)(this + 0x6f4) | 0x800;
    DAT_011308e8 = 0;
    DAT_011308e0 = '\x01';
  }
  // Handle pending lobby join action
  if ((*(uint *)(this + 0x6f4) >> 2 & 1) != 0) {
    (**(code **)(*(int *)(this + 0x378) + 0x94))(); // Call joinLobby callback
    *(uint *)(this + 0x6f4) = *(uint *)(this + 0x6f4) & 0xfffffffb;
  }
  // Handle lobby state change (bit 0xB)
  if ((*(uint *)(this + 0x6f4) >> 0xb & 1) != 0) {
    bVar5 = DAT_011308e0 != '\0';
    if (bVar5) {
      DAT_011308e0 = '\0';
    }
    else {
      _DAT_011308e4 = DAT_01205228;
    }
    DAT_011308e8 = (uint)!bVar5;
    DAT_011307fc = 0;
    FUN_009c8f10(DAT_011307f8); // Clear lobby data
    DAT_011307f8 = 0;
    DAT_01130800 = 0;
    uStack_8 = CONCAT44(uStack_8._4_4_,(undefined4)uStack_8);
    if (DAT_0112b9b4 != 0) {
      iVar3 = FUN_00963f80(*(undefined4 *)(this + 0x1b8)); // Get player list
      if (iVar3 == 0) {
        FUN_009631c0(); // Handle no players
        uStack_8 = CONCAT44(uStack_8._4_4_,(undefined4)uStack_8);
        if (((*(int *)(this + 0x3c8) != 0) &&
            (uStack_8 = CONCAT44(uStack_8._4_4_,(undefined4)uStack_8),
            **(int **)(this + 0x3c4) != 0)) &&
           (uStack_8 = CONCAT44(uStack_8._4_4_,(undefined4)uStack_8),
           *(int *)(**(int **)(this + 0x3c4) + 0x10) != 2)) {
          FUN_00964350(2); // Set game state to 2 (lobby?)
        }
      }
      else {
        uVar1 = *(uint *)(iVar3 + 8);
        if (uVar1 != 0) {
          do {
            iVar2 = *(int *)(*(int *)(iVar3 + 4) + uVar4 * 4);
            if (iVar2 != 0) {
              uVar6 = FUN_0095c290(iVar2 + 0x17c,iVar2 + 0x180); // Get player name
              uStack_8 = uVar6;
              FUN_0095e000(&uStack_8); // Process player name
            }
            uVar4 = uVar4 + 1;
          } while (uVar4 < uVar1);
        }
      }
    }
    // Copy lobby state data
    *(undefined1 *)(this + 0x160) = *(undefined1 *)(this + 500);
    // Update lobby UI with various parameters
    FUN_00966090(*(undefined4 *)(this + 0x120),*(undefined4 *)(this + 0x128),
                 *(undefined4 *)(this + 300),*(undefined4 *)(this + 0x130),
                 *(undefined4 *)(this + 0x138),*(undefined4 *)(this + 0xe4),
                 *(undefined4 *)(this + 0x114),*(undefined4 *)(this + 0x124),
                 *(undefined4 *)(this + 0xfc),*(undefined4 *)(this + 0x104));
    // Show lobby screen
    FUN_005a04a0("ShowLobby",0,&DAT_00d8cdec,0);
    // Deactivate button if needed
    if (*(char *)(this + 0x144) == '\0') {
      FUN_005a04a0("DeactivateButton",0,&DAT_00d8cdec,1,&DAT_00d796d0);
    }
    // Set flags
    *(uint *)(this + 0x6f4) = *(uint *)(this + 0x6f4) | 4;
    *(uint *)(this + 0x6f4) = *(uint *)(this + 0x6f4) & 0xfffff7ff;
  }
  return 0;
}