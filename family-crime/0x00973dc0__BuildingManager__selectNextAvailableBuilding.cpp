// FUNC_NAME: BuildingManager::selectNextAvailableBuilding
void __thiscall selectNextAvailableBuilding(int param_1, int param_2)

{
  uint buildingCount;
  uint index;
  uint nextIndex;
  uint selectedIndex;
  
  buildingCount = *(uint *)(param_1 + 0x50); // +0x50: buildingCount
  index = 0;
  if (buildingCount != 0) {
    selectedIndex = buildingCount + ((*(uint *)(param_1 + 0x60) & ((int)*(uint *)(param_1 + 0x60) < 1) - 1) + buildingCount
                    + param_2) % buildingCount; // +0x60: currentSelectedIndex
    do {
      nextIndex = selectedIndex % buildingCount;
      if ((&buildingAvailabilityFlags)[nextIndex * 3] == 0) { // Check if building is available (0 = available)
        if (nextIndex != 0xffffffff) {
          *(uint *)(param_1 + 0x60) = nextIndex; // Update current selected index
          FUN_005a04a0("UpdateSelection", 0, &DAT_00d8f604, 0); // Log selection change
          local_c = DAT_011302b0; // Some global or class data
          local_8 = 0;
          local_4 = 0;
          FUN_00408a00(&local_c, 0); // Handle selection change (likely UI update)
          return;
        }
        break;
      }
      index = index + 1;
      selectedIndex = selectedIndex + (uint)(-1 < param_2) * 2 + -1; // Adjust search direction (param_2 positive = forward, negative = backward)
    } while (index < buildingCount);
  }
  // No available building found - set to "none" or "cancel" state
  local_c = DAT_011301f8; // Some default "no selection" value
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c, 0); // Clear selection
  return;
}