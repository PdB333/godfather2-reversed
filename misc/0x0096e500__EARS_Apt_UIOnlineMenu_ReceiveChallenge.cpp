// Xbox PDB: EARS_Apt_UIOnlineMenu_ReceiveChallenge
// FUNC_NAME: MultiplayerScenario::processHostHandshake
void __thiscall MultiplayerScenario::processHostHandshake(int *this, int param_2, int hostId, int gameId, int playerId)
{
  bool bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int local_8;
  uint local_4;
  
  // +0x1E4 = m_state (0x79*4), +0xDC = m_bHost (0x37*4)
  if ((this[0x79] == 1) && (this[0x37] == 1)) {
    uVar4 = 0;
    bVar1 = false;
    local_8 = 0;
    local_4 = 0;
    // +0x17C = m_hostsCount (0x5f*4)
    if (this[0x5f] != 0) {
      do {
        // +0x178 = m_hosts (0x5e*4) - array of pointers
        iVar3 = *(int *)(this[0x5e] + uVar4 * 4);
        iVar5 = local_8;
        uVar2 = local_4;
        // Check if host matches ID and gameId, but playerId differs
        if (((*(int *)(iVar3 + 0xf0) == hostId) && (*(int *)(iVar3 + 0xf4) == gameId)) &&
           (iVar5 = iVar3, uVar2 = uVar4, *(int *)(iVar3 + 0x100) != playerId)) {
          // Clear old playerId, remove host, cleanup
          FUN_0096ad30(iVar3 + 0x100); // clearPlayerId
          FUN_009c8eb0(*(undefined4 *)(this[0x5e] + uVar4 * 4)); // releaseHost
          FUN_00963970(uVar4); // removeHostByIndex
          bVar1 = true;
          iVar5 = local_8;
          uVar2 = local_4;
        }
        local_4 = uVar2;
        local_8 = iVar5;
        uVar4 = uVar4 + 1;
      } while (uVar4 < (uint)this[0x5f]);
      if (bVar1) {
        FUN_005a04a0("ClearHostsList",0,&DAT_00d8cdec,0); // debugLog
        // +0x2EC = m_callback (0xbb*4), offset 0x6C = onHostsCleared
        (**(code **)(this[0xbb] + 0x6c))(0);
      }
      if (local_8 != 0) {
        FUN_00968e40(&playerId, local_8 + 0x100); // copyPlayerId
        iVar3 = FUN_00967dd0(param_2); // getGamePhase
        if (playerId == 0) {
          return;
        }
        if (iVar3 == 3) {
          return;
        }
        iVar5 = *(int *)(playerId + 4); // related field
        if (iVar3 == 2) {
          if (iVar5 == 0) {
            FUN_00983190(); // showLoadingScreen
            FUN_0096d150(local_8); // setupForJoin
            iVar5 = 3;
          }
        }
        else if (iVar3 == 0) {
          if (iVar5 == 2) {
            (**(code **)(*this + 0xc))(); // vtable method
            FUN_00983190(); // showLoadingScreen
            FUN_00983120("$mp_online_enter_don_sitdown",0,0); // showMessage
          }
        }
        else if ((iVar3 == 1) && (iVar5 != 1)) {
          iVar5 = 0;
        }
        // +0x108 = m_status (0x42*4)
        this[0x42] = iVar5;
        // +0x10C = m_selectedHostIndex (0x43*4)
        this[0x43] = local_4;
        FUN_005a04a0("SetStatus",0,&DAT_00d8cdec,0); // debugLog
        FUN_00968ea0(&param_2, local_8 + 0x100); // copyGameId
        *(int *)(param_2 + 4) = iVar5; // setStatus
        return;
      }
    }
    iVar3 = FUN_00967dd0(param_2);
    if (iVar3 == 2) {
      FUN_00964d00(hostId, gameId); // requestHostRefresh
    }
  }
  return;
}