// FUNC_NAME: GodfatherGameManager::shutdown
void __fastcall GodfatherGameManager::shutdown(int this)
{
  // Call base class or engine shutdown
  FUN_0096abb0();
  
  // Release audio data manager (likely a singleton or manager pointer at +0x6C)
  FUN_009c8f10(*(undefined4 *)(this + 0x6c));
  
  // Handle vehicle manager or similar subsystem at +0x58
  int vehicleManager = *(int *)(this + 0x58);
  if (vehicleManager != 0) {
    // Release audio component of vehicle manager (+8 offset)
    FUN_009c8f10(*(undefined4 *)(vehicleManager + 8));
    // Destroy vehicle manager object
    FUN_009c8eb0(vehicleManager);
  }
  
  // Release building manager or similar at +0x4C
  if (*(int *)(this + 0x4c) != 0) {
    FUN_009c8f10(*(int *)(this + 0x4c));
  }
  
  // Final engine cleanup
  FUN_005c16e0();
  return;
}