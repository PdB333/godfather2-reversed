// FUNC_NAME: GodfatherGameManager::shutdown
void __fastcall GodfatherGameManager::shutdown(int thisPtr)
{
  // Shutdown various subsystems
  FUN_00976d00(0); // e.g., AudioDataManager::shutdown
  FUN_0094b210(0); // e.g., InputDeviceManager::shutdown
  FUN_00785db0(0); // e.g., StreamManager::shutdown
  FUN_004df630();  // e.g., lockMutex
  FUN_004df630();  // e.g., lockMutex (double lock? or different mutex)
  FUN_00979b10(0); // e.g., EntityDataManager::shutdown
  FUN_004df600();  // e.g., unlockMutex

  // Check bit 2 of flags at +0x60, if set, unregister a callback and clear the bit
  if ((*(uint *)(thisPtr + 0x60) >> 2 & 1) != 0) {
    FUN_005c02f0(thisPtr + 0x10, FUN_00979ac0, 1); // e.g., unregisterCallback
    *(uint *)(thisPtr + 0x60) = *(uint *)(thisPtr + 0x60) & 0xfffffffb; // Clear bit 2
  }

  FUN_004df650();  // e.g., unlockMutex
  FUN_0097a310(0); // e.g., NetSession::shutdown

  // Check global pointer at DAT_01130040 + 0x60 for non-zero, then call shutdown
  if (*(int *)(DAT_01130040 + 0x60) != 0) {
    FUN_00991cd0(); // e.g., OnlineServices::shutdown
  }

  FUN_004df600();  // e.g., unlockMutex
  // Clear bit 6 of flags at +0x60 (e.g., mark as not initialized)
  *(uint *)(thisPtr + 0x60) = *(uint *)(thisPtr + 0x60) & 0xffffffbf;
  return;
}