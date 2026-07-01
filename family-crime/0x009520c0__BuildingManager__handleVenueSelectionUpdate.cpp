// FUNC_NAME: BuildingManager::handleVenueSelectionUpdate
undefined4 __thiscall BuildingManager::handleVenueSelectionUpdate(int thisPtr, int param2)
{
  int iVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  iVar3 = FUN_00466840(); // getCurrentVenueId
  iVar1 = param2;
  if (param2 == iVar3) {
    iVar1 = *(int *)(thisPtr + 0x98); // +0x98: currentVenueState
    if (iVar1 == 1) {
      FUN_00951b60(2); // setVenueState(2)
      return 0;
    }
    if ((iVar1 != 2) && (iVar1 != 3)) {
      return 0;
    }
    FUN_00951b60(1); // setVenueState(1)
    return 0;
  }
  iVar3 = FUN_00466860(); // getCurrentBuildingTypeId
  if (iVar1 == iVar3) {
    cVar2 = FUN_00957d00(); // isBuildingTypeSelectionActive
    local_8 = 0;
    local_4 = 0;
    if (cVar2 == '\0') {
      local_c = DAT_011302c0; // some global string/ID
      FUN_00408a00(&local_c,0); // logMessage
      return 0;
    }
    local_c = DAT_01130310; // another global string/ID
    FUN_00408a00(&local_c,0); // logMessage
    return 0;
  }
  switch(iVar1) {
  case 0: // VENUE_ACTION_NONE
  case 3: // VENUE_ACTION_VIEW
  case 5: // VENUE_ACTION_UNKNOWN
    return 1;
  case 6: // VENUE_ACTION_BUY
    uVar4 = 0xffffffff;
    goto LAB_00952303;
  case 7: // VENUE_ACTION_SELL
    uVar4 = 1;
LAB_00952303:
    cVar2 = FUN_00951a10(*(undefined4 *)(thisPtr + 0x68),thisPtr + 0xa0,uVar4,&DAT_011304d8,
                         &DAT_011302c0); // tryVenueTransaction
    if (cVar2 != '\0') {
      FUN_00951970(500); // setTimer(500)
      FUN_005a04a0("UpdateVenueSelection",0,&DAT_00d8bc74,0); // logEvent
      return 0;
    }
    break;
  case 8: // VENUE_ACTION_BUILD
    param2 = *(undefined4 *)(thisPtr + 0x78); // +0x78: selectedBuildingTypeId
    *(undefined4 *)(thisPtr + 0xa0) = 0xffffffff; // clear venueId
    cVar2 = FUN_00951a10(*(undefined4 *)(thisPtr + 0x5c),&param2,1,&DAT_011301c0,&DAT_011302c0); // tryBuildingConstruction
    if (cVar2 != '\0') {
      FUN_00952030(param2); // onBuildingConstructionStarted
      FUN_00951e50(1); // setBuildingMode(1)
      FUN_00951970(500); // setTimer(500)
      if ((*(int *)(thisPtr + 0x78) != -1) && (*(char *)(thisPtr + 0x48) != '\0')) {
        FUN_00956a50(*(int *)(thisPtr + 0x78),0); // updateBuildingUI
      }
      FUN_005a04a0("UpdateBuildingTypeSelection",0,&DAT_00d8bc74,0); // logEvent
      return 0;
    }
    break;
  case 9: // VENUE_ACTION_UPGRADE
    param2 = *(undefined4 *)(thisPtr + 0x78); // +0x78: selectedBuildingTypeId
    *(undefined4 *)(thisPtr + 0xa0) = 0xffffffff; // clear venueId
    cVar2 = FUN_00951a10(*(undefined4 *)(thisPtr + 0x5c),&param2,0xffffffff,&DAT_011301c0,
                         &DAT_011302c0); // tryBuildingUpgrade
    if (cVar2 != '\0') {
      FUN_00952030(param2); // onBuildingUpgradeStarted
      FUN_00951e50(1); // setBuildingMode(1)
      FUN_00951970(500); // setTimer(500)
      if ((*(int *)(thisPtr + 0x78) != -1) && (*(char *)(thisPtr + 0x48) != '\0')) {
        FUN_00956a50(*(int *)(thisPtr + 0x78),0); // updateBuildingUI
      }
      FUN_005a04a0("UpdateBuildingTypeSelection",0,&DAT_00d8bc74,0); // logEvent
      return 0;
    }
    break;
  case 10: // VENUE_ACTION_CANCEL
    if (*(int *)(thisPtr + 0x98) == 1) {
      FUN_00951b60(3); // setVenueState(3)
      return 0;
    }
    if (*(int *)(thisPtr + 0x98) == 2) {
      FUN_00951ad0(); // cancelVenueAction
      return 0;
    }
    break;
  case 0xc: // VENUE_ACTION_CLOSE
    FUN_00951e50(0); // setBuildingMode(0)
  }
  return 0;
}