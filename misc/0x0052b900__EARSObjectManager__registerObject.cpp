// FUNC_NAME: EARSObjectManager::registerObject
void EARSObjectManager::registerObject(void)
{
  undefined4 uVar1;
  
  // Call virtual function at vtable+0x04 to get object ID
  uVar1 = (**(code **)(PTR_PTR_01125d80 + 4))();
  
  // Store object ID in global table
  _DAT_01125d88 = FUN_0060d740(uVar1);
  
  // Call virtual function at vtable+0x10 (likely post-registration)
  (**(code **)(PTR_PTR_01125d80 + 0x10))();
  
  // Store current object pointer
  _DAT_01125d84 = DAT_012058ec;
  
  // Increment object count
  DAT_012058f8 = DAT_012058f8 + 1;
  
  // Store object pointer in list
  DAT_012058ec = &PTR_PTR_01125d80;
  
  // Store object count
  _DAT_01125d8c = DAT_012058f8;
  
  return;
}