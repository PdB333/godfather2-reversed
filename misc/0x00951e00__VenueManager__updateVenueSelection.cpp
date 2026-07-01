// FUNC_NAME: VenueManager::updateVenueSelection
void __fastcall VenueManager::updateVenueSelection(int this)
{
  // Check if venue is active (0x48), not completed (0x4c), 
  // current venue index (0x78) is less than total venues (0x5c),
  // and the venue at current index (0x58 + index*4) is null/empty
  if ((((*(char *)(this + 0x48) != '\0') && (*(char *)(this + 0x4c) != '\0')) &&
      (*(uint *)(this + 0x78) < *(uint *)(this + 0x5c))) &&
     (*(int *)(*(int *)(this + 0x58) + *(uint *)(this + 0x78) * 4) == 0)) {
    // Trigger venue selection callback
    FUN_00957350();
  }
  
  // Log update event
  FUN_005a04a0("UpdateVenueSelection", 0, &DAT_00d8bc74, 0);
  
  // Update venue state machine
  FUN_005c1b40();
}