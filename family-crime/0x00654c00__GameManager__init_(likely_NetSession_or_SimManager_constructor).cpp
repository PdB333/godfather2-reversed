// FUNC_NAME: GameManager::init (likely NetSession or SimManager constructor)
void GameManager::init(int *pListener, undefined4 param_2, undefined4 param_3) {
  uint *pCount;
  int idx;
  undefined4 handle;
  bool bAlreadyInitialized;
  
  // Set vtable pointer (class-specific vtable at 0x00e43130)
  this->vtable = &VTable_00e43130;
  
  // Zero out many fields (offsets in terms of ints, 4 bytes each)
  this->field_04 = 0;   // +0x04
  this->field_08 = 0;   // +0x08
  this->field_14 = 0;   // +0x14 (5*4)
  this->field_0C = 0;   // +0x0C
  this->field_10 = 0;   // +0x10
  this->field_20 = 0;   // +0x20 (8*4) - pointer to array
  this->field_18 = 0;   // +0x18 (6*4) - count (uint)
  this->field_1C = 0;   // +0x1C (7*4)
  this->field_2C = 0;   // +0x2C (11*4)
  this->field_24 = 0;   // +0x24 (9*4)
  this->field_28 = 0;   // +0x28 (10*4)
  this->field_30 = 0;   // +0x30 (12*4)
  this->field_34 = 0;   // +0x34 (13*4)
  
  // Call subsystem initialization functions
  initSubsystemA();     // FUN_0065c920
  initSubsystemB();     // FUN_00658010
  initSubsystemC();     // FUN_0064cd90
  
  // Check and manage global singleton (DAT_01205a64)
  if (gGlobalManager != NULL) {
    // Call vfunc +12 on existing global manager (cleanup?)
    gGlobalManager->vtable->cleanup();
  }
  gGlobalManager = pListener;  // Register new listener/manager
  
  if (pListener != NULL) {
    // Call vfunc +8 on the new listener (init?)
    pListener->vtable->init();
  }
  
  // Allocate 0x78 (120) bytes for a child object
  int *pChild = allocateMemory(0x78);  // FUN_009c8e50
  if (pChild != NULL) {
    initializeChild(pChild, param_3);  // FUN_0065ceb0 - passes param_3
  }
  
  // Check global flag (DAT_0120588f)
  bAlreadyInitialized = (gInitFlag == 0);
  this->field_6C = 0;       // +0x6C (27*4)
  this->field_7C = 1;       // +0x7C (31*4) - byte set to 1
  this->field_68 = 0;       // +0x68 (26*4) - byte set to 0
  
  if (bAlreadyInitialized) {
    gInitFlag = 1;
    initGlobalData(&gGlobalData);    // FUN_00662100
    initGlobalData2(&gGlobalData);   // FUN_006622a0
  }
  
  // Copy 12 bytes from global data into this object at offset 0x70 (28*4)
  copyData(&this->field_70, 12, &gGlobalData);  // FUN_00662350
  
  // Register a callback or event with ID 0x81 (129)
  registerEvent(0x81);   // FUN_00657bf0
  
  // Set count field at +0x18 to 129, ensuring it's exactly 129
  pCount = &this->field_18;  // Actually puVar1 = unaff_EDI+6, so at +0x18
  if ((*pCount < 0x81) || (0x81 < *pCount)) {
    *pCount = 0x81;
  }
  
  // Zero out an array of 129 elements (each 4 bytes) pointed to by field at +0x20
  for (idx = 0; idx < (int)*pCount; idx++) {
    ((uint *)this->field_20)[idx] = 0;
  }
  
  this->field_80 = 0;   // +0x80 (32*4)
  
  // Obtain a handle and store at +0x64 (25*4)
  handle = acquireHandle();   // FUN_0065c190
  this->field_64 = handle;
  return;
}