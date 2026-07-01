// Xbox PDB: EARS_Apt_UIOnlineMenu_LookUpGameComplete
// FUNC_NAME: MPJoinManager::processJoinState

undefined1 __thiscall MPJoinManager::processJoinState(MPJoinManager* thisPtr, MPLobbySession* session)
{
  char cVar1;
  undefined1 retVal;
  undefined4 uVar3;
  int* piVar4;
  int iVar5;
  int* piVar6;
  uint joinFlags;
  undefined1* puVar8;
  int iVar9;
  undefined4 unaff_EDI;
  int* piVar10;
  undefined2 in_FPUControlWord;
  char* pcVar11;
  undefined8 local_stack_50;
  undefined4 local_stack_48;
  code* local_pcStack_44;
  int* local_piStack_40;
  undefined4 local_uStack_3c;
  undefined4 local_uStack_38;
  code* local_pcStack_34;
  undefined1* local_puStack_30;
  undefined4 local_uStack_2c;
  undefined4 local_uStack_28;
  code* local_pcStack_24;
  undefined1* local_apuStack_20[3];
  code* local_pcStack_14;
  int local_iStack_c;
  
  FUN_00982c90(); // init join state
  piVar6 = session;
  local_stack_50._0_4_ = (undefined1*)(uint)(ushort)local_stack_50;
  local_stack_50 = CONCAT44(DAT_01223484, (undefined1*)local_stack_50); // store global flag
  if ((session != (MPLobbySession*)0x0) && (DAT_01223484 != 0)) {
    uVar3 = (**(code**)(*session + 0xc))(); // get session status
    local_piStack_40 = (int*)(**(code**)(*piVar6 + 0x10))(); // get session data
    local_uStack_3c = uVar3;
    session = (MPLobbySession*)FUN_00964230(&local_piStack_40); // check join status (returns 0 if ok)
    if (session == (MPLobbySession*)0x0) {
      piVar4 = (int*)(**(code**)(*piVar6 + 0x50))(); // get config
      cVar1 = (**(code**)(*piVar4 + 0x28))("DonMode", 0); // check if don mode
      if (cVar1 == '\0') {
        iVar5 = thisPtr[0x37]; // this->joinState
        if (iVar5 != 7) {
          thisPtr[0x31] = 0; // this->someStateVar1
          thisPtr[0x35] = 0; // this->stateTimer
          switch(iVar5) {
          case 1:
          case 6:
            iVar9 = 9;
            break;
          default:
            iVar9 = 10;
          }
          thisPtr[0x36] = iVar9; // this->stateSubTimer
          if (iVar5 == 4) {
            FUN_005a04a0("HideReadyState", 0, &DAT_00d8cdec, 0); // hide UI
          }
          if (thisPtr[0x37] == 1) { // joinState == INIT
            FUN_0096adc0(); // cancel any existing join
          }
          piVar10 = thisPtr + 4; // pointer to handlers array
          FUN_005c02f0(piVar10, &LAB_00969090, 1); // register handler
          FUN_005c02f0(piVar10, &LAB_00963ee0, 1);
          FUN_005c02f0(piVar10, &LAB_0096fba0, 1);
          FUN_005c02f0(piVar10, &LAB_0096ee00, 1);
          thisPtr[0x37] = 7; // set state to WAITING_FOR_CONFIRMATION
          FUN_00965720(); // start timer
        }
      }
      else {
        FUN_00970400(1); // set join mode to don
      }
      iVar5 = (**(code**)(*piVar4 + 0x30))("MatchTypeIndex", 0); // get match type
      thisPtr[0x6a] = iVar5; // store match type
      thisPtr[0x6d] = 0; // reset some index
      iVar5 = FUN_009c8e50(0x108); // allocate UI overlay (size 0x108)
      if (iVar5 == 0) {
        session = (MPLobbySession*)0x0;
        FUN_0096ac70(&session); // create default UI
      }
      else {
        session = (MPLobbySession*)FUN_00962840(piVar6); // clone session data
        FUN_0096ac70(&session); // attach overlay
      }
    }
    else {
      FUN_00960030(piVar6); // handle join error
    }
    uVar2 = FUN_0089c630(); // get some random/flag
    local_stack_48 = CONCAT31(local_stack_48._1_3_, uVar2);
    uVar7 = thisPtr[0x1bd]; // joinFlags
    local_piStack_40 = thisPtr + 0x6a; // pointer to lobby data block
    piVar4 = session;
    piVar10 = local_piStack_40;
    // copy lobby data from session to this (0x42 ints = 0x108 bytes)
    for (iVar5 = 0x42; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar10 = *piVar4;
      piVar4 = piVar4 + 1;
      piVar10 = piVar10 + 1;
    }
    if ((uVar7 >> 1 & 1) != 0) { // FLAG_JOIN_IN_PROGRESS
      piVar4 = (int*)thunk_FUN_00b0d810(2, 0x10, 0x10); // allocate packet
      piVar6 = local_stack_50._4_4_;
      uVar2 = FUN_008a2a80();
      local_pcStack_44 = (code*)CONCAT31(local_pcStack_44._1_3_, uVar2);
      (**(code**)(*piVar4 + 0x2c))("JoinerStrictNAT", local_pcStack_44); // set NAT attribute
      (**(code**)(*piVar4 + 0x2c))("IsPlayerDon", (undefined1*)local_stack_50); // set don flag
      (**(code**)(*thisPtr + 0xc))(); // notify join start
      FUN_0096f7a0("$mp_joining_game", 0); // show joining message
      (**(code**)(*piVar6 + 0x90))(*(undefined4*)(local_iStack_c + 0xfc), *(undefined4*)(local_iStack_c + 0x100), piVar4, 0); // send join request
      return 1;
    }
    if ((uVar7 >> 0xe & 1) == 0) { // FLAG_JOIN_RESPONSE_RECEIVED (not set)
      // no response yet
    }
    else {
      // response received
      cVar1 = FUN_0096ee90(piVar6); // check if join accepted
      local_stack_50._0_3_ = CONCAT12(cVar1, (ushort)local_stack_50);
      if (cVar1 != '\0') goto LAB_00973117;
    }
  }
  // cleanup if session disconnected or error
  if ((*(int*)((int)local_stack_50._4_4_ + 0x28) != 0 || *(int*)((int)local_stack_50._4_4_ + 0x2c) != 0) &&
     ((undefined4*)((int)local_stack_50._4_4_ + 0x28) != (undefined4*)0x0)) {
    *(undefined4*)((int)local_stack_50._4_4_ + 0x28) = 0;
    *(undefined4*)((int)local_stack_50._4_4_ + 0x2c) = 0;
    DAT_011308b5 = 0;
  }
  (**(code**)(*thisPtr + 8))(); // call parent destructor?
  FUN_00983120(0, 0, 0); // reset UI
  if (local_stack_50._3_1_ == '\0') {
    iVar5 = FUN_009c8e50(0xf0); // allocate error overlay
    if (iVar5 == 0) {
      iVar5 = 0;
    }
    else {
      iVar5 = FUN_00982280(0); // init UI
    }
    pcVar11 = "$mp_join_error";
  }
  else {
    FUN_0095e840(); // handle join accepted
    FUN_00970400(0); // reset join mode
    iVar5 = FUN_009c8e50(0xf0); // allocate error overlay
    if (iVar5 == 0) {
      iVar5 = 0;
      pcVar11 = "$mp_online_menu_map_unavailable";
    }
    else {
      iVar5 = FUN_00982280(0);
      pcVar11 = "$mp_online_menu_map_unavailable";
    }
  }
  FUN_00981eb0(pcVar11); // show error title
  *(undefined4*)(iVar5 + 0xc) = 3; // set error type
  *(code**)(iVar5 + 0x14) = FUN_00982b30; // set close callback
  FUN_00982e10(); // apply UI
  thisPtr[0x1bd] = thisPtr[0x1bd] & 0xfffffffd; // clear FLAG_JOIN_IN_PROGRESS
  if (thisPtr[0x79] == 2) { // if InGameState == 2 (returning to menu)
    FUN_00967e30(); // handle disconnect
  }
LAB_00973117:
  return local_stack_50._2_1_; // return byte (maybe success/failure)
}