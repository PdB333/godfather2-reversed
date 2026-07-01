// FUNC_NAME: BuildingManager::processBuildingAction
void __thiscall BuildingManager::processBuildingAction(int thisPtr, int stateMachineState, int actionType)
{
    bool bVar1;
    
    // +0x48 offset: buildingCount (number of buildings)
    if (1 < *(uint *)(thisPtr + -0x48)) {
        // Sort buildings by priority using comparator at 0x008f3290
        // +0x2058 offset: building array start
        _qsort((void *)(thisPtr + -0x2058), *(uint *)(thisPtr + -0x48), 0x558,
               (_PtFuncCompare *)&LAB_008f3290);
    }
    
    // Check if this is an upgrade action (state 1, type 3 = upgrade complete?)
    if ((stateMachineState == 1) && (actionType == 3)) {
        bVar1 = true;
    }
    else {
        bVar1 = false;
    }
    
    // +0x2084 offset: currentMenuState (0=none, 2=building menu, 5=construction)
    if (*(int *)(thisPtr + -0x2084) == 2) {
        if (bVar1) {
            // Upgrade completed while in building menu
            FUN_008f42f0(); // updateBuildingListUI
            FUN_008f5fe0(0); // closeBuildingMenu(0)
            return;
        }
        if (stateMachineState == 0) {
            FUN_008f61d0(); // handleBuildingMenuExit
            return;
        }
    }
    else {
        if (*(int *)(thisPtr + -0x2084) != 5) {
            return; // Not in any relevant state
        }
        if (stateMachineState == 0) {
            if (*(int *)(thisPtr + -0x48) != 1) {
                FUN_008f5760(); // openBuildingSelection
                return;
            }
            FUN_008f44b0(0); // placeBuilding(0)
            return;
        }
        if (bVar1) {
            FUN_008f2cf0(0); // completeConstruction(0)
            return;
        }
    }
    
    // Default: handle other state transitions
    FUN_008f3ea0(); // updateConstructionUI
    FUN_008f2cf0(stateMachineState); // transitionConstructionState
    return;
}