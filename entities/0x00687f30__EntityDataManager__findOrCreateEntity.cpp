// FUNC_NAME: EntityDataManager::findOrCreateEntity
EntityDataManager* __thiscall EntityDataManager::findOrCreateEntity(EntityDataManager* this, int param_1, undefined4 param_2)
{
  int result;
  undefined4 uVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  // Structure passed to memory allocation:
  // +0x00: unknown1 = 2
  // +0x04: unknown2 = 16
  // +0x08: unknown3 = 0
  local_c = 2;
  local_8 = 0x10;
  local_4 = 0;
  
  // Allocate memory for entity (size 0x1D0 = 464 bytes)
  result = FUN_0043b980(0x1d0, &local_c, param_2);
  if (result != 0) {
    // Initialize entity from the current object
    uVar2 = FUN_00890a80(param_1);
    return uVar2;
  }
  return 0;
}