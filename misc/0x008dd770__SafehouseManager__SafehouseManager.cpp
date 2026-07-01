// FUNC_NAME: SafehouseManager::SafehouseManager

undefined4 * __thiscall SafehouseManager::SafehouseManager(undefined4 *this, undefined4 param1)
{
  undefined4 *allocPtr;
  undefined4 unknownGlobal;
  undefined4 *newArray;
  undefined4 *arrayBase;
  int messageId;
  
  g_safehouseManagerGlobal = this;
  this[0x1] = &PTR_FUN_00e2f19c;  // vtable or interface pointer
  this[0x2] = 1;                    // some count or flag
  this[0x3] = 0;                    // some counter
  this[0x4] = &PTR_LAB_00e30fe0;   // another vtable or table
  this[0x0] = &PTR_FUN_00d7e934;   // main vtable
  *(this + 0x1) = &PTR_LAB_00d7e924; // override vtable at +0x04
  this[0x4] = &PTR_LAB_00d7e914;   // override vtable at +0x10
  this[0xA] = 0;                    // +0x28: pointer, later set
  *(short *)(this + 0xB) = 0;      // +0x2C: short (padding?)
  *(short *)((int)this + 0x2E) = 0; // +0x2E: short (padding?)
  *(byte *)(this + 0xC) = 0;       // +0x30: byte flags, later OR 8
  
  // Allocate array of 25 SafehouseEvent nodes (each 0xC bytes)
  allocPtr = (undefined4 *)allocateMemory(0x130); // 0x130 = 25 * 0xC + maybe header?
  if (allocPtr == (undefined4 *)0x0) {
    arrayBase = (undefined4 *)0x0;
  }
  else {
    arrayBase = allocPtr + 1; // skip header? allocPtr[0] = 0x19 (count)
    *allocPtr = 0x19;         // store count at start
    // Construct 25 elements using default constructor at LAB_008dd760
    _vector_constructor_iterator_(arrayBase, 0xC, 0x19, (_func_void_ptr_void_ptr *)&LAB_008dd760);
  }
  unknownGlobal = DAT_00d7e910;   // some global constant
  this[0x9] = arrayBase;          // +0x24: store array pointer
  this[0x5] = 3;                  // +0x14: some count
  this[0x6] = unknownGlobal;      // +0x18
  this[0x7] = unknownGlobal;      // +0x1C
  this[0x8] = unknownGlobal;      // +0x20
  
  // Register message handlers
  messageId = findMessageID(&DAT_012069c4, "iMsgTransferStolenMoney");
  if (messageId != 0) {
    registerMessageCallback(this + 0x1, &DAT_012069c4, 0x8000); // callback flag
  }
  registerMessage(this + 0xA, "iMsgTransferStolenMoney"); // store message ID
  
  // Look up other message IDs
  findMessageID(&DAT_0112fc60, "iMsgPlayerHasEnteredSafehouse");
  if (DAT_0112fc60 != 0) {
    registerMessageCallback(this + 0x1, &DAT_0112fc60, 0x8000);
  }
  findMessageID(&DAT_0112fc6c, "iMsgSafehouseSetPlayerOwned");
  findMessageID(&DAT_0112fc74, "iMsgEnableSafehouseTeleport");
  if (DAT_0112fc74 != 0) {
    registerMessageCallback(this + 0x1, &DAT_0112fc74, 0x8000);
  }
  findMessageID(&DAT_0112fc7c, "iMsgDisableSafehouseTeleport");
  if (DAT_0112fc7c != 0) {
    registerMessageCallback(this + 0x1, &DAT_0112fc7c, 0x8000);
  }
  
  // Set flag bit 3 at offset +0x30
  *(byte *)(this + 0xC) = *(byte *)(this + 0xC) | 8;
  
  // Unknown setup call with param1
  FUN_00463980(0x9ab67f60, this + 0x4, param1);
  
  return this;
}