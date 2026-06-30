// FUNC_NAME: EARSMemoryManager::allocatePool
void EARSMemoryManager::allocatePool(void)

{
  undefined4 uVar1;
  
  uVar1 = (**(code **)(DAT_01219940 + 4))();  // Call vtable[1] (likely a constructor/initializer)
  _DAT_01219948 = FUN_0060d740(uVar1);  // Convert handle/pointer to some identifier
  (**(code **)(DAT_01219940 + 0x10))();  // Call vtable[4] (second element in 4-slot vtable)
  _DAT_01219944 = DAT_012058ec;  // Save previous pool list head
  DAT_012058f8 = DAT_012058f8 + 1;  // Increment global pool counter
  DAT_012058ec = &DAT_01219940;  // Set global pool list head to this pool
  _DAT_0121994c = DAT_012058f8;  // Store pool index
  return;
}