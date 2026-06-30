// FUNC_NAME: SomeManager::SomeManager
undefined4 * __thiscall SomeManager::SomeManager(undefined4 *this, byte allocFlag)
{
  *this = &PTR_FUN_00e310ac; // vtable pointer
  this[2] = &PTR_LAB_00e310b8; // secondary vtable or base pointer at +0x08
  initializeSubsystem(&PTR_LAB_00e310a0); // initialize with a label
  this[2] = &PTR_LAB_00e310bc; // update to another vtable/base pointer
  g_globalCounter = 0; // DAT_01223424 = 0
  resetSomeFlag(); // FUN_0049c640
  if ((allocFlag & 1) != 0) {
    operatorDelete(this); // FUN_009c8eb0 - deallocate if flag set
  }
  return this;
}