// FUNC_NAME: GameManager::GameManager
undefined4 * __thiscall GameManager::GameManager(undefined4 *this, byte allocFlag)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d7ad64;
  // Initialize function pointers at offsets 0x3C and 0x48
  this[0xf] = &PTR_LAB_00d7ad54;
  this[0x12] = &PTR_LAB_00d7ad50;
  // Initialize global subsystems
  FUN_004086d0(&DAT_0112f4b4);
  FUN_00408310(&DAT_0112f4b4);
  FUN_008b2820();
  // If allocFlag bit 0 is set, deallocate? (likely a custom allocator pattern)
  if ((allocFlag & 1) != 0) {
    FUN_0043b960(this, 0x90);
  }
  return this;
}