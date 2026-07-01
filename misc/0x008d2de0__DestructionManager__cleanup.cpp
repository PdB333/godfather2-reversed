// FUNC_NAME: DestructionManager::cleanup
void __fastcall DestructionManager::cleanup(undefined4 *this)
{
  *this = &PTR_FUN_00d7d464; // vtable assignment
  this[0xf] = &PTR_LAB_00d7d454; // +0x3C: some function pointer
  this[0x12] = &PTR_LAB_00d7d450; // +0x48: another function pointer
  if (this[0x14] != 0) { // +0x50: pointer to allocated memory/object
    FUN_004086d0(this + 0x14); // deallocate/release
    FUN_00408310(this + 0x14); // free memory
  }
  FUN_0046c640(); // probably DestructionManager::shutdown or similar global cleanup
}