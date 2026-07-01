// FUNC_NAME: MissionManager::loadMission
void __thiscall MissionManager::loadMission(MissionManager *this, IMissionData *pMissionData)
{
  uint type; // eax? Not stored
  int iVar1;
  char *source;
  undefined4 id;
  int globalGameManager;
  int *pplugin;
  
  globalGameManager = g_gameManager; // DAT_01223484
  if (globalGameManager == 0) {
    return;
  }
  // Allocate mission data structure (size 0x60)
  iVar1 = allocateMissionData(0x60);
  if (iVar1 != 0) {
    // Initialize vtable or something? (FUN_008a2dd0 with args 0,3,0,0,0)
    FUN_008a2dd0(0,3,0,0,0);
    // Initialize fields at offsets
    *(uint *)(iVar1 + 0x50) = 0; // +0x50: missionDriverIndex or something?
    *(uint *)(iVar1 + 0x54) = 0; // +0x54: unknown
    *(byte *)(iVar1 + 0x58) = 0; // +0x58: bool
    *(byte *)(iVar1 + 0x59) = 0; // +0x59: bool
    *(uint *)(iVar1 + 0x5c) = 0; // +0x5c: missionID
  }
  // Copy mission name from interface
  source = (char *)pMissionData->getName(); // vtable offset +4
  _strncpy((char *)(iVar1 + 0x20), source, 0x30); // +0x20: name buffer (48 bytes)
  *(byte *)(iVar1 + 0x4f) = 0; // +0x4f: null terminator or something
  *(byte *)(iVar1 + 0x58) = 0; // +0x58: bool (re-initialized, maybe flag for audio?)
  // Set type to 2 (missionType = SYSTEM_INITIALIZE? or something)
  *(uint *)(iVar1 + 0x10) = 2;
  
  // Get mission ID from interface
  id = pMissionData->getId(); // vtable offset +12
  *(uint *)(iVar1 + 0x5c) = id;
  
  // Choose resource loading path based on global flag (likely multiplayer vs singleplayer)
  if (*(int *)(globalGameManager + 8) == 0) {
    // Singleplayer: use this->resourceLoaderSP (vtable +0x88)
    (*(code **)(*(int *)(this + 0x378) + 0x88))(iVar1);
  } else {
    // Multiplayer: use this->resourceLoaderMP (vtable +0x88)
    (*(code **)(*(int *)(this + 0x2ec) + 0x88))();
    // Then re-get ID and call something
    id = pMissionData->getId();
    FUN_009646b0(id);
  }
  
  // Switch based on mission type stored in this->missionType (+0xdc)
  switch(*(uint *)(this + 0xdc)) {
  case 1: // MISSION_TYPE_MAIN or similar
    // Set this->missionState (+0x1e4) to 3
    *(uint *)(this + 0x1e4) = 3;
    // Initialize mission timer at this+0x1a8
    initMissionTimer((int *)(this + 0x1a8)); // FUN_008a3be0
    // Set mission data's state (+0x14) to 1 (missionInitialized)
    *(uint *)(iVar1 + 0x14) = 1;
    // Call subsystem initiation functions
    initWorldState(1);  // FUN_00967d70
    initAIControllers(); // FUN_00962d80
    initGameplayOverlays(); // FUN_00970f10
    break;
  case 3: // MISSION_TYPE_TUTORIAL or something
    *(uint *)(iVar1 + 0x14) = 4; // missionFinished? or missionCompleted
    return;
  case 0xc: // MISSION_TYPE_MULTISTAGE or something
    // Call some UI initialization with this->someUIPointer (+0x6e8)
    initMissionUI(*(int *)(this + 0x6e8)); // FUN_00967c80
    // Fall through to common case (5,7,0xb)
  case 5:
  case 7:
  case 0xb:
    *(uint *)(iVar1 + 0x14) = 4; // mission state = completed? More likely "waiting for next step"
    // Get a plugin/extension from somewhere (FUN_00965910)
    iVar3 = getMissionPlugin(); // returns a vtable pointer or object
    if (iVar3 != 0) {
      pplugin = (int *)getMissionPlugin();
      // Call vtable method at offset +0x94 (likely finalize or something)
      (*(code **)(*pplugin + 0x94))();
      return;
    }
    break;
  }
  return;
}