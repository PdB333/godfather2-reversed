// FUNC_NAME: GodfatherGameManager::handleDebugCommand
undefined1 __thiscall GodfatherGameManager::handleDebugCommand(int *this)
{
  char cVar1;
  undefined1 uVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 in_stack_00000010;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined8 uStack_10;
  undefined4 uStack_8;
  
  uVar2 = 1;
  switch(in_stack_00000010) {
  case 0x31: // '1' - disable debug flag
    uVar4 = FUN_006252f0(); // getDebugFlagMask
    *(uint *)(this[0x16] + 0x1b94) = *(uint *)(this[0x16] + 0x1b94) & ~uVar4;
    return 1;
  case 0x32: // '2' - enable debug flag
    uVar4 = FUN_006252f0(); // getDebugFlagMask
    *(uint *)(this[0x16] + 0x1b94) = *(uint *)(this[0x16] + 0x1b94) | uVar4;
    return 1;
  case 0x33: // '3' - toggle debug overlay
    FUN_007ea0b0(); // toggleDebugOverlay
    return 1;
  case 0x34: // '4' - spawn debug entity
    iVar5 = (**(code **)(*(int *)this[0x1f] + 0x34))(); // getEntityManager
    FUN_0046ffe0(iVar5 + 0x20,0); // clearEntityList
    (**(code **)(*this + 0x2c))(0xc996f012,1,1,0,0x3f800000,0x3f800000); // spawnEntity
    return 1;
  case 0x35: // '5' - start mission
    FUN_0045f2a0(0); // resetMissionState
    puVar6 = (undefined4 *)FUN_007ab130(); // getGameManager
    (**(code **)*puVar6)(0x3f); // setGameState
    FUN_007ea5e0(0,this,this[0x16]); // startMission
    cVar1 = FUN_00481660(); // isMissionReady
    if (cVar1 != '\0') {
      uVar7 = 0x18; // mission ID
LAB_007eaaf2:
      FUN_0079fb90(uVar7,1,0,uStack_10,uStack_8); // triggerMissionEvent
      FUN_00472130(0); // updateMission
      return 1;
    }
    break;
  case 0x36: // '6' - enable debug camera
    FUN_007f63e0(0x10); // setDebugCameraMode
    return 1;
  case 0x37: // '7' - disable debug camera
    FUN_007f6420(0x10); // clearDebugCameraMode
    piVar3 = (int *)FUN_007ab130(); // getGameManager
    (**(code **)(*piVar3 + 4))(this[0x1d]); // restoreCamera
    return 1;
  case 0x38: // '8' - toggle debug features
    FUN_007f6420(0x23); // clearDebugFlag1
    FUN_007f6420(0x24); // clearDebugFlag2
    return 1;
  case 0x39: // '9' - spawn debug NPC
    uVar8 = 0;
    uVar7 = FUN_006fbc40(); // getNPCTemplate
    FUN_007f96a0(0,0,uVar7,uVar8); // spawnNPC
    FUN_006fbc70(); // finalizeNPCSpawn
    return 1;
  case 0x3a: // ':' - start alternate mission
    FUN_0045f2a0(0); // resetMissionState
    puVar6 = (undefined4 *)FUN_007ab130(); // getGameManager
    (**(code **)*puVar6)(0x3f); // setGameState
    FUN_007ea5e0(1,this,this[0x16]); // startMission
    cVar1 = FUN_00481660(); // isMissionReady
    if (cVar1 != '\0') {
      uVar7 = 0x17; // alternate mission ID
      goto LAB_007eaaf2;
    }
    break;
  default:
    uVar2 = FUN_007abec0(); // handleUnknownCommand
  }
  return uVar2;
}