// Xbox PDB: EARS_Apt_LeaderboardsScreen_SortList
// FUNC_NAME: OnlineLobbyScreen::onStateChange
void __thiscall OnlineLobbyScreen::onStateChange(int this, int newStateId)
{
  int stateValue;
  int *pManager;
  int iVar3;
  char *strBuf;
  undefined8 uVar5;
  undefined1 *local_30_strPtr;
  undefined4 local_2c;
  undefined4 local_28;
  code *local_24_freeFunc;
  undefined1 *local_20_strPtr2;
  undefined4 local_1c;
  undefined4 local_18;
  code *local_14_freeFunc2;
  undefined1 *local_10_strArray[3];
  code *local_4_freeFunc3;

  // Get current state from some network manager (likely NetSession)
  stateValue = (**(code **)(*(int *)(DAT_01130048 + 0x10) + 4))();
  if (newStateId == stateValue) {
    // State matches: handle highlight/clear logic
    if (*(char *)(DAT_01130048 + 0x68) != '\0') {
      uVar5 = FUN_00965910(); // Get some manager object (maybe MultiplayerScenarioManager?)
      pManager = (int *)uVar5;
      if (pManager != (int *)0x0) {
        // Call virtual method at +0xa0 with param (this->+0xdc == 1 ?)
        (**(code **)(*pManager + 0xa0))
                  (*(undefined4 *)((int)((ulonglong)uVar5 >> 0x20) + 100),
                   *(int *)(this + 0xdc) == 1);
        // Unhighlight previous title
        FUN_005a04a0("UnhighlightSortedTitle", 0, &DAT_00d8cdec, 0);
        // Set new title index
        *(undefined4 *)(this + 0x110) = *(undefined4 *)(DAT_01130048 + 100);
        FUN_005a04a0("HighlightSortedTitle", 0, &DAT_00d8cdec, 0);
        // Copy some value from +0x17c to +0xe0
        *(undefined4 *)(this + 0xe0) = *(undefined4 *)(this + 0x17c);
        FUN_005a04a0("ClearHostsList", 0, &DAT_00d8cdec, 0);
        // Call virtual method at +0x6c with 0
        (**(code **)(*pManager + 0x6c))(0);
        FUN_005a04a0("UpdateScroll", 0, &DAT_00d8cdec, 0);
        return;
      }
    }
  }
  else {
    // Not the same state: try other state comparisons
    iVar3 = (**(code **)(*(int *)(DAT_011307e8 + 0x10) + 4))();
    int baseAddr = DAT_01129930;
    if (newStateId == iVar3) {
      // Handle offer wager state
      if (*(char *)(DAT_011307e8 + 0x134) == '\0') {
        *(undefined1 *)(this + 500) = 0;
        *(undefined1 *)(DAT_01129914 + 0xd3) = 0;
        FUN_0095eb90(0);
        return;
      }
      iVar3 = *(int *)(DAT_011307e8 + 0x60);
      if (iVar3 == 0) {
        *(undefined4 *)(DAT_01129930 + 0x1e0) = 0;
        *(undefined4 *)(baseAddr + 0x23c) = 0;
        FUN_00970ca0();
        return;
      }
      int dialogHandle = FUN_009c8e50(0xf0);
      if (dialogHandle == 0) {
        dialogHandle = 0;
      }
      else {
        dialogHandle = FUN_00982280(0);
      }
      FUN_00981ec0("$mp_offer_wager");
      // Initialize string buffers
      local_20_strPtr2 = (undefined1 *)0x0;
      local_1c = 0;
      local_18 = 0;
      local_14_freeFunc2 = (code *)0x0;
      local_30_strPtr = (undefined1 *)0x0;
      local_2c = 0;
      local_28 = 0;
      local_24_freeFunc = (code *)0x0;
      FUN_00604000(iVar3, &local_30_strPtr, 1);
      char* tempStr = local_30_strPtr;
      if (local_30_strPtr == (undefined1 *)0x0) {
        tempStr = &DAT_0120546e; // empty string
      }
      FUN_004d4a60(local_10_strArray, 1, "{w:%s}{$mp_offer_wager_description}", tempStr);
      char* descStr = local_10_strArray[0];
      if (local_10_strArray[0] == (undefined1 *)0x0) {
        descStr = &DAT_0120546e;
      }
      FUN_00603970(&local_20_strPtr2, descStr);
      char* finalStr = local_20_strPtr2;
      if (local_20_strPtr2 == (undefined1 *)0x0) {
        finalStr = &DAT_0120546e;
      }
      FUN_00981eb0(finalStr);
      *(undefined4 *)(dialogHandle + 0xc) = 9;
      *(code **)(dialogHandle + 0x14) = FUN_00982b30;
      FUN_00981e70("$mp_online_menu_yes", 1, 0);
      FUN_00981e70("$mp_online_menu_no", 0, 0);
      *(undefined1 **)(dialogHandle + 0x14) = &LAB_00971810; // set callback
      FUN_00982e10();
      // Free temporary strings
      if (local_10_strArray[0] != (undefined1 *)0x0) {
        (*local_4_freeFunc3)(local_10_strArray[0]);
      }
      if (local_30_strPtr != (undefined1 *)0x0) {
        (*local_24_freeFunc)(local_30_strPtr);
      }
      if (local_20_strPtr2 != (undefined1 *)0x0) {
        (*local_14_freeFunc2)(local_20_strPtr2);
        return;
      }
    }
    else {
      // Check other states for returning to main menu
      if ((((*(char *)(this + 0x2e0) == '\0') && (DAT_01223484 != 0)) &&
          (*(int *)(DAT_01223484 + 0x28) != 0 || *(int *)(DAT_01223484 + 0x2c) != 0)) &&
         (DAT_01223484 != -0x28)) {
        iVar3 = (**(code **)(*(int *)(DAT_01130064 + 0x10) + 4))();
        if (newStateId != iVar3) {
          iVar3 = (**(code **)(*(int *)(DAT_0113000c + 0x10) + 4))();
          if (newStateId != iVar3) {
            FUN_009718a0(); // go back to main menu?
            return;
          }
        }
      }
      DAT_011308b5 = 0;
    }
  }
  return;
}