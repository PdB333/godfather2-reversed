// FUNC_NAME: PoolManager::PoolManager
// Description: Constructor for a pool manager that creates and manages a fixed-size array of slot objects.
// Each slot holds a pointer to a pooled item (0x20 bytes each). An internal manager object (0x28 bytes) handles pool operations.
// The pool is initialized with a global singleton pointer, a count of slots, and a callback.

PoolManager* __thiscall PoolManager::PoolManager(PoolManager* this, uint slotCount, uint unkParam3, uint unkParam4, int allocExtraCount, PoolManager* callbackHandler)
{
  bool bCleanedUp;
  uint32 uVar2;
  uint32 uVar3;
  int* piSlotPtr;
  int local_10;
  uint32 local_c;
  uint32 local_8;
  uint32 local_4;
  int* local_poolInner;
  
  // Store this as global singleton
  g_poolManagerSingleton = this;
  
  this->field_08 = slotCount;                     // +0x08: slot count
  this->vtable_ptr = &PoolManager_vtable;         // +0x00: vtable
  this->field_10 = 0;                             // +0x10
  this->field_14 = 0;                             // +0x14
  this->field_18 = 0;                             // +0x18
  bCleanedUp = false;
  this->field_20 = unkParam4;                     // +0x20
  this->field_24 = unkParam3;                     // +0x24

  // Allocate aligned memory for internal data (0x2c bytes per element, alignment 4, count = allocExtraCount + 3)
  uVar2 = (uint32)alignedAlloc(0x2c, 4, allocExtraCount + 3);
  uVar3 = (uint32)reinterpret_cast(uVar2);
  
  // Create inner manager object (size 0x28)
  int* pInnerManager = (int*)alloc(0x28);
  if (pInnerManager != (int*)0x0) {
    *pInnerManager = &PoolInner_vtable;              // +0x00: vtable
    memcopy(uVar3, uVar2, 0x2c, 4);                  // Copy 4 * 0x2c bytes (??)
    pInnerManager[9] = 1;                            // +0x24
    initSomeCounter(0);
  }
  this->innerManager = pInnerManager;            // +0x04

  // Allocate array of slot storage (slotCount * 4 bytes)
  uVar2 = reinterpret_cast(slotCount * 4);       // sign-extended or 64-bit safe
  this->slotArray = (uint32*)uVar2;              // +0x0C

  // Initialize each slot
  uint idx = 0;
  int* tempPtr = local_poolInner;
  if (slotCount != 0) {
    do {
      int* pSlot = (int*)alloc(0x20);
      if (pSlot != (int*)0x0) {
        int* pInner = (int*)this->innerManager;   // Re-read inner manager pointer
        local_c = 0;
        local_8 = 0;
        local_4 = 0;
        local_poolInner = pInner;
        // Call virtual function at offset 8 on inner manager
        (**(code**)(*pInner + 8))();
        local_10 = initFromValues(&local_c, pInner);  // Initialize from stack values
        bCleanedUp = true;
        uVar2 = createSlotObject(&local_poolInner);   // Create a slot object
      }
      // Store slot pointer in the array
      this->slotArray[idx] = uVar2;
      if (bCleanedUp) {
        bCleanedUp = false;
        if (local_10 != 0) {
          // Call virtual destructor at offset 4 on the inner manager's raw pointer
          (**(code**)(*pInner + 4))(local_10, 0);
          local_10 = 0;
        }
        // Call virtual method at offset 12 on inner manager
        (**(code**)(*pInner + 0xc))();
      }
      idx++;
    } while (idx < slotCount);
  }

  // Register callback
  registerCallback(callbackHandler);
  this->callbackHandler = callbackHandler;       // +0x1C
  return this;
}