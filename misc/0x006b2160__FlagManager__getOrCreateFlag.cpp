// FUNC_NAME: FlagManager::getOrCreateFlag
int __fastcall FlagManager::getOrCreateFlag(int this)
{
  // Check if the flag at offset +0xe4 has been set/initialized
  // If the flag pointer is null, create a new one using FUN_00603330
  // which likely initializes the flag at +0xe0 and assigns it to +0xe4
  if (*(int *)(this + 0xe4) == 0) {
    // FUN_00603330 is likely flag creation/initialization function
    // +0xdc: some parameter/resource handle
    // +0xe0: flag data storage
    FUN_00603330(*(undefined4 *)(this + 0xdc), this + 0xe0);
  }
  
  // Return pointer to the flag data at offset +0xe0
  return this + 0xe0;
}