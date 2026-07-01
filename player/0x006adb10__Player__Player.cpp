// FUNC_NAME: Player::Player

undefined4 * __thiscall Player::Player(Player *this, undefined4 allocatorPtr)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  
  // Allocate 0x4000 bytes using the allocator
  FUN_0046e6b0(allocatorPtr, 0x4000);

  // Initialize fields
  this->field_0x188 = 0;            // +0x188
  this->field_0x18c = 0;            // +0x18c
  this->field_0x190 = DAT_00d5ccf8; // +0x190

  // vtable pointer
  this->vtable = &PTR_FUN_00d5dca0; // +0x00

  // Additional vtable pointers for multiple inheritance / interfaces
  this->interfaceTable_0x3c = &PTR_LAB_00d5dc90;   // +0x3c
  this->interfaceTable_0x48 = &PTR_LAB_00d5dc8c;   // +0x48
  this->interfaceTable_0x50 = &PTR_LAB_00d5dc88;   // +0x50
  this->interfaceTable_0x54 = &PTR_LAB_00d5dc28;   // +0x54
  this->interfaceTable_0x58 = &PTR_LAB_00d5dbc0;   // +0x58

  this->field_0x180 = 0;            // +0x180
  this->field_0x184 = 0;            // +0x184
  this->field_0x194 = uVar2;        // +0x194 (uVar2 = DAT_00d5ddec)
  this->field_0x198 = 0;            // +0x198
  this->field_0x19c = 0;            // +0x19c
  this->field_0x1a0 = 0;            // +0x1a0

  // Initialize a linked list or array of objects (probably 5 slots)
  piVar4 = &this->field_0x1ac;      // +0x1ac
  puVar1 = &this->field_0x1a4;      // +0x1a4

  this->field_0x1a8 = puVar1;        // +0x1a8
  *puVar1 = puVar1;                  // Self-pointing list head
  *piVar4 = 0;                       // +0x1ac = 0

  // Zero out many fields in the range 0x1b0 .. 0x1dc
  this->field_0x1b0 = 0;            // +0x1b0
  this->field_0x1b4 = 0;            // +0x1b4
  this->field_0x1b8 = 0;            // +0x1b8
  this->field_0x1bc = 0;            // +0x1bc
  this->field_0x1c0 = 0;            // +0x1c0
  this->field_0x1c4 = 0;            // +0x1c4
  this->field_0x1c8 = 0;            // +0x1c8
  this->field_0x1cc = 0;            // +0x1cc
  this->field_0x1d0 = 0;            // +0x1d0
  this->field_0x1d4 = 0;            // +0x1d4
  this->field_0x1d8 = 0;            // +0x1d8
  this->field_0x1dc = 0;            // +0x1dc

  // Two shorts at offset 0x1e0 and 0x1e2
  *(short *)&this->field_0x1e0 = 0; // +0x1e0
  *(short *)((int)&this->field_0x1e0 + 2) = 0; // +0x1e2

  FUN_006b6d40(); // Some subsystem initialization

  // Clear a series of "slot" structures (each slot = int + 2 shorts)
  // Slot 0 starts at offset 0x23c
  this->slotInt_0x23c = 0;          // +0x23c
  *(short *)&this->slotShort_0x240 = 0; // +0x240
  *(short *)((int)&this->slotShort_0x240 + 2) = 0; // +0x242

  this->slotInt_0x244 = 0;          // +0x244
  *(short *)&this->slotShort_0x248 = 0; // +0x248
  *(short *)((int)&this->slotShort_0x248 + 2) = 0; // +0x24a

  this->slotInt_0x24c = 0;          // +0x24c
  *(short *)&this->slotShort_0x250 = 0; // +0x250
  *(short *)((int)&this->slotShort_0x250 + 2) = 0; // +0x252

  this->slotInt_0x254 = 0;          // +0x254
  *(short *)&this->slotShort_0x258 = 0; // +0x258
  *(short *)((int)&this->slotShort_0x258 + 2) = 0; // +0x25a

  this->slotInt_0x25c = 0;          // +0x25c
  *(short *)&this->slotShort_0x260 = 0; // +0x260
  *(short *)((int)&this->slotShort_0x260 + 2) = 0; // +0x262

  // Slot 5 has constants (likely identifier)
  this->slotInt_0x264 = 0x850d90a8; // +0x264
  this->slotInt_0x268 = 0x6213b2d1; // +0x268

  this->slotInt_0x26c = 0;          // +0x26c
  *(short *)&this->slotShort_0x270 = 0; // +0x270
  *(short *)((int)&this->slotShort_0x270 + 2) = 0; // +0x272

  this->slotInt_0x274 = 0;          // +0x274
  *(short *)&this->slotShort_0x278 = 0; // +0x278
  *(short *)((int)&this->slotShort_0x278 + 2) = 0; // +0x27a

  this->slotInt_0x27c = 0;          // +0x27c
  *(short *)&this->slotShort_0x280 = 0; // +0x280
  *(short *)((int)&this->slotShort_0x280 + 2) = 0; // +0x282

  this->slotInt_0x284 = 0;          // +0x284
  *(short *)&this->slotShort_0x288 = 0; // +0x288
  *(short *)((int)&this->slotShort_0x288 + 2) = 0; // +0x28a

  this->slotInt_0x28c = 0;          // +0x28c
  *(short *)&this->slotShort_0x290 = 0; // +0x290
  *(short *)((int)&this->slotShort_0x290 + 2) = 0; // +0x292

  this->slotInt_0x294 = 0;          // +0x294
  *(short *)&this->slotShort_0x298 = 0; // +0x298
  *(short *)((int)&this->slotShort_0x298 + 2) = 0; // +0x29a

  this->slotInt_0x29c = 0;          // +0x29c
  *(short *)&this->slotShort_0x2a0 = 0; // +0x2a0
  *(short *)((int)&this->slotShort_0x2a0 + 2) = 0; // +0x2a2

  this->slotInt_0x2a4 = 0;          // +0x2a4
  *(short *)&this->slotShort_0x2a8 = 0; // +0x2a8
  *(short *)((int)&this->slotShort_0x2a8 + 2) = 0; // +0x2aa

  this->slotInt_0x2ac = 0;          // +0x2ac
  *(short *)&this->slotShort_0x2b0 = 0; // +0x2b0
  *(short *)((int)&this->slotShort_0x2b0 + 2) = 0; // +0x2b2

  *(char *)((int)&this->slotInt_0x2ac + 4) = 0; // +0x2b4

  // Free any existing pointers in the 5-slot array (offsets 0x1ac,0x1b4,0x1bc,0x1c4,0x1cc)
  piVar4 = &this->field_0x1ac; // start of pointer array
  iVar3 = 5;
  do {
    if (*piVar4 != 0) {
      FUN_004daf90(piVar4); // delete object
      *piVar4 = 0;
    }
    piVar4 = piVar4 + 2; // advance by 8 bytes (two ints)
    iVar3--;
  } while (iVar3 != 0);

  // Re-zero some of the slot fields (perhaps redundant)
  this->slotInt_0x244 = 0;
  this->slotInt_0x24c = 0;
  this->slotInt_0x2ac = 0;
  this->slotInt_0x23c = 0;
  this->slotInt_0x254 = 0;
  this->slotInt_0x274 = 0;
  this->slotInt_0x26c = 0;
  this->slotInt_0x25c = 0;
  this->slotInt_0x28c = 0;
  this->slotInt_0x294 = 0;

  // Register a message handler for "iMsgPressurePlayerBreakingDestructibles"
  FUN_00408240(&DAT_0112a588, "iMsgPressurePlayerBreakingDestructibles");

  // If a specific global pointer is non-zero, register it with the interface at +0x3c
  if (DAT_0120e93c != 0) {
    FUN_00408900(&this->interfaceTable_0x3c, &DAT_0120e93c, 0x8000);
  }

  this->selfPointer = this; // +0x238

  return this;
}