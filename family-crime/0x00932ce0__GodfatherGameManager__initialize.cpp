// FUNC_NAME: GodfatherGameManager::initialize
void __fastcall GodfatherGameManager::initialize(int thisPtr)
{
  // Set bit 6 (0x40) in global flags
  DAT_01130590 = DAT_01130590 | 0x40;
  
  // Call initialization helper
  FUN_00566b70();
  
  // Call virtual function at vtable+0x2c (likely on some manager object)
  (**(code **)(*DAT_011305a0 + 0x2c))();
  
  // Check if a specific subsystem is active (DAT_01129828 + 0x2c)
  if (*(int *)(DAT_01129828 + 0x2c) != 0) {
    FUN_008f1f40();
  }
  
  // Set global state to 0x11 (17 decimal - likely an enum value)
  DAT_00e5672c = 0x11;
  
  // Clear field at +0x60 (likely a pointer or flag)
  *(undefined4 *)(thisPtr + 0x60) = 0;
  
  // Check if bit 0 is not set in global flags
  if ((DAT_01130590 & 1) == 0) {
    // Register callback with offset +0x14 (likely a timer or event handler)
    FUN_005c0d50(thisPtr + 0x14, &LAB_00931e00, 0);
    
    // Set bit 0 in global flags
    DAT_01130590 = DAT_01130590 | 1;
  }
}