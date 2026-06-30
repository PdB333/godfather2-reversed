// FUNC_NAME: SingletonManager::getInstance
undefined * FUN_00691a70(void)

{
  // Check if the singleton has been initialized (bit 0 of _DAT_01129c64)
  if ((_DAT_01129c64 & 1) == 0) {
    // Mark as initialized
    _DAT_01129c64 = _DAT_01129c64 | 1;
    
    // Initialize singleton data
    _DAT_01129c54 = 1;          // +0x04: reference count or initialized flag
    _DAT_01129c58 = 0;          // +0x08: some counter or state
    _DAT_01129c50 = &PTR_FUN_00d5c948;  // +0x00: vtable pointer or function table
    _DAT_01129c5c = 0;          // +0x0C: some data
    DAT_01129c60 = 0;           // +0x10: byte data
    DAT_01129c61 = 0;           // +0x11: byte data
    DAT_01129c62 = 0;           // +0x12: byte data
    DAT_01129c63 = 0;           // +0x13: byte data
    
    // Register cleanup function to be called on exit
    _atexit((_func_4879 *)&LAB_00d51540);
  }
  
  // Return pointer to the singleton instance (base of the data block)
  return &DAT_01129c50;
}