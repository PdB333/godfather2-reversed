// FUNC_NAME: SomeClass::registerSyncMessage
void SomeClass::registerSyncMessage(uint32_t param_1)

{
  uint32_t *puVar1;
  uint32_t local_c; // Message type
  uint32_t local_8; // Flags?
  uint32_t local_4; // Some ID or offset
  
  puVar1 = (uint32_t *)FUN_009c8f80(); // Get some global object pointer
  local_c = 2;   // Message type: e.g., SyncState
  local_8 = 0x10; // Flags: e.g., reliable, immediate
  local_4 = 0;    // No additional data/ID
  (**(code **)*puVar1)(param_1, &local_c); // Call function pointer with message struct
  return;
}