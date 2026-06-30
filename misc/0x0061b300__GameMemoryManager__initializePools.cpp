// FUNC_NAME: GameMemoryManager::initializePools
void GameMemoryManager::initializePools(void)

{
  undefined4 allocFlags; // local_18
  undefined4 allocSize; // local_14
  undefined4 alignment; // local_10
  undefined4 extraFlags; // uStack_c
  
  // First allocation: 0xC80 (3200) bytes, flags: 2 (maybe alignment flag), size: 0x10 (16 bytes)
  allocFlags = 2;
  allocSize = 0x10;
  alignment = 0;
  DAT_01205978 = (**(code **)*DAT_01205868)(0xc80,&allocFlags); // +0x00: pool1 pointer
  
  // Second allocation: 500 bytes, flags: 2, size: 0x10 (16 bytes), extraFlags: 0
  allocSize = 2;
  alignment = 0x10;
  extraFlags = 0;
  _DAT_012059c8 = (**(code **)*DAT_01205868)(500,&allocSize); // +0x50: pool2 pointer
  
  // Initialize pool sizes and counts
  _DAT_012059a4 = DAT_00e2b1a4; // +0x2C: pool1 element size
  _DAT_012059a8 = DAT_00e2b1a4; // +0x30: pool1 element count
  _DAT_012059ac = DAT_00e2b1a4; // +0x34: pool1 total size
  
  _DAT_01205974 = 0; // +0x04: pool1 free count
  _DAT_0120597c = DAT_01205978; // +0x08: pool1 current pointer
  _DAT_012059c4 = 0; // +0x4C: pool2 free count
  
  _DAT_012059b4 = 0xb; // +0x3C: pool2 element size (11 bytes)
  _DAT_012059b0 = 0; // +0x38: pool2 current index
  
  _DAT_0120598c = 0; // +0x14: some counter
  _DAT_01205990 = 0; // +0x18: some counter
  _DAT_01205994 = 1; // +0x1C: some flag
  _DAT_01205998 = 1; // +0x20: some flag
  
  _DAT_012059b8 = DAT_00e2cd54; // +0x40: pool2 element size
  _DAT_012059bc = DAT_00e2cd54; // +0x44: pool2 element count
  
  _DAT_01205970 = 0; // +0x00: some base pointer
  
  // Initialize the pool system
  _DAT_01205970 = FUN_0061bdf0(); // Call pool initialization function
  
  return;
}