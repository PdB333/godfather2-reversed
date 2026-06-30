// FUNC_NAME: BuildingSystem::updateBuildingByIndex
void __thiscall BuildingSystem::updateBuildingByIndex(int param_1)
{
  // this pointer (in_EAX) points to some structure with fields:
  // +0x00: int id         (local_20)
  // +0x04: float progress (local_1c)
  // global g_maxProgress is compared but unused
  // g_buildingManager is a global singleton instance of BuildingSystem
  // g_buildingArray is a global array of Building* (indexed by district*11 + param_1)
  // global g_currentDistrict determines which district block to use

  undefined4 local_20;
  float local_1c;
  undefined4 local_18;
  float local_14;

  local_20 = *(undefined4*)this;                    // building id
  local_1c = *(float*)((char*)this + 4);            // building progress
  local_14 = g_maxProgress - local_1c;              // unused difference

  // Access building pointer from global array: district * 11 + param_1
  int index = g_currentDistrict * 11 + param_1;
  if (g_buildingArray[index] != 0) {
    local_18 = local_20;                            // copy id to pass
    FUN_0060add0(g_buildingManager, g_buildingArray[index], &local_20); // apply effect to target building
  }
  return;
}