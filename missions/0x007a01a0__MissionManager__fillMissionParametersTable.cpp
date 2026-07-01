// FUNC_NAME: MissionManager::fillMissionParametersTable
void __thiscall MissionManager::fillMissionParametersTable
                  (MissionManager *this,undefined4 param_2,undefined4 param_3,
                  undefined4 param_4,undefined4 param_5,undefined4 param_6)

{
  char bCanAllocate;
  int pEntry;
  
  bCanAllocate = FUN_00481640();  // Likely checks if mission system is initialized or active
  if (bCanAllocate != '\0') {
    pEntry = FUN_009c8e50(0x50);  // Memory allocation of 0x50 bytes (80 bytes) for a mission parameter entry
    if (pEntry == 0) {
      pEntry = 0;
    }
    else {
      pEntry = FUN_007a0030(this);  // Constructor/initialization of the entry object, passing 'this'
    }
    *(undefined4 *)(pEntry + 0x38) = param_2;  // +0x38: first parameter value
    *(undefined4 *)(pEntry + 0x3c) = param_3;  // +0x3c: second parameter value
    *(undefined4 *)(pEntry + 0x40) = param_4;  // +0x40: third parameter value
    *(undefined4 *)(pEntry + 0x44) = param_5;  // +0x44: fourth parameter value
    *(undefined4 *)(pEntry + 0x48) = param_6;  // +0x48: fifth parameter value
    FUN_00481690(pEntry);  // Registers/adds the entry to the mission system's internal list
  }
  return;
}