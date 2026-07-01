// Xbox PDB: EARS::Modules::Building::Building
// FUNC_NAME: CGameMessageSender::constructor
undefined4 * __thiscall CGameMessageSender::constructor(undefined4 *this, undefined4 param_2)
{
  undefined4 *piVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  
  // Initialize with a buffer size of 0x4000 (16KB)
  FUN_0046e6b0(param_2,0x4000);
  
  // Initialize message queue counters
  this[0x62] = 0; // +0x188
  this[99] = 0;   // +0x18C
  this[100] = DAT_00d5ccf8; // +0x190
  
  uVar2 = DAT_00d5ddec;
  
  // Set up virtual function table
  *this = &PTR_FUN_00d5dca0;
  
  // Set up various function pointers
  this[0xf] = &PTR_LAB_00d5dc90;   // +0x3C
  this[0x12] = &PTR_LAB_00d5dc8c;  // +0x48
  this[0x14] = &PTR_LAB_00d5dc88;  // +0x50
  this[0x15] = &PTR_LAB_00d5dc28;  // +0x54
  this[0x16] = &PTR_LAB_00d5dbc0;  // +0x58
  
  // More initialization
  this[0x60] = 0; // +0x180
  this[0x61] = 0; // +0x184
  this[0x65] = uVar2; // +0x194
  this[0x66] = 0; // +0x198
  this[0x67] = 0; // +0x19C
  this[0x68] = 0; // +0x1A0
  
  // Initialize circular buffer/list structure
  piVar4 = this + 0x6b; // +0x1AC
  piVar1 = this + 0x69; // +0x1A4
  this[0x6a] = piVar1;  // +0x1A8 -> points to +0x1A4
  *piVar1 = piVar1;     // self-referencing pointer
  *piVar4 = 0;          // +0x1AC = 0
  
  // Zero out many fields
  this[0x6c] = 0; // +0x1B0
  this[0x6d] = 0; // +0x1B4
  this[0x6e] = 0; // +0x1B8
  this[0x6f] = 0; // +0x1BC
  this[0x70] = 0; // +0x1C0
  this[0x71] = 0; // +0x1C4
  this[0x72] = 0; // +0x1C8
  this[0x73] = 0; // +0x1CC
  this[0x74] = 0; // +0x1D0
  this[0x75] = 0; // +0x1D4
  this[0x76] = 0; // +0x1D8
  this[0x77] = 0; // +0x1DC
  
  *(undefined2 *)(this + 0x78) = 0;   // +0x1E0
  *(undefined2 *)((int)this + 0x1e2) = 0; // +0x1E2
  
  // Initialize sub-system
  FUN_006b6d40(); // MessageSender sub-system init
  
  // Initialize numerous message type tracking arrays
  // Each group appears to be: value (int) + high part (short) + padding/short
  this[0x8f] = 0;   // +0x23C
  *(undefined2 *)(this + 0x90) = 0;     // +0x240
  *(undefined2 *)((int)this + 0x242) = 0; // +0x242
  
  this[0x91] = 0;   // +0x244
  *(undefined2 *)(this + 0x92) = 0;     // +0x248
  *(undefined2 *)((int)this + 0x24a) = 0; // +0x24A
  
  this[0x93] = 0;   // +0x24C
  *(undefined2 *)(this + 0x94) = 0;     // +0x250
  *(undefined2 *)((int)this + 0x252) = 0; // +0x252
  
  this[0x95] = 0;   // +0x254
  *(undefined2 *)(this + 0x96) = 0;     // +0x258
  *(undefined2 *)((int)this + 0x25a) = 0; // +0x25A
  
  this[0x97] = 0;   // +0x25C
  *(undefined2 *)(this + 0x98) = 0;     // +0x260
  *(undefined2 *)((int)this + 0x262) = 0; // +0x262
  
  this[0x99] = 0x850d90a8; // +0x264 - Magic constant
  this[0x9a] = 0x6213b2d1; // +0x268 - Magic constant
  this[0x9b] = 0; // +0x26C
  *(undefined2 *)(this + 0x9c) = 0;     // +0x270
  *(undefined2 *)((int)this + 0x272) = 0; // +0x272
  
  this[0x9d] = 0; // +0x274
  *(undefined2 *)(this + 0x9e) = 0;     // +0x278
  *(undefined2 *)((int)this + 0x27a) = 0; // +0x27A
  
  this[0x9f] = 0; // +0x27C
  *(undefined2 *)(this + 0xa0) = 0;     // +0x280
  *(undefined2 *)((int)this + 0x282) = 0; // +0x282
  
  this[0xa1] = 0; // +0x284
  *(undefined2 *)(this + 0xa2) = 0;     // +0x288
  *(undefined2 *)((int)this + 0x28a) = 0; // +0x28A
  
  this[0xa3] = 0; // +0x28C
  *(undefined2 *)(this + 0xa4) = 0;     // +0x290
  *(undefined2 *)((int)this + 0x292) = 0; // +0x292
  
  this[0xa5] = 0; // +0x294
  *(undefined2 *)(this + 0xa6) = 0;     // +0x298
  *(undefined2 *)((int)this + 0x29a) = 0; // +0x29A
  
  this[0xa7] = 0; // +0x29C
  *(undefined2 *)(this + 0xa8) = 0;     // +0x2A0
  *(undefined2 *)((int)this + 0x2a2) = 0; // +0x2A2
  
  this[0xa9] = 0; // +0x2A4
  *(undefined2 *)(this + 0xaa) = 0;     // +0x2A8
  *(undefined2 *)((int)this + 0x2aa) = 0; // +0x2AA
  
  this[0xab] = 0; // +0x2AC
  *(undefined2 *)(this + 0xac) = 0;     // +0x2B0
  *(undefined2 *)((int)this + 0x2b2) = 0; // +0x2B2
  
  *(undefined1 *)(this + 0xad) = 0; // +0x2B4
  
  // Loop to clean up 5 items at +0x1AC stepping by +8 (pointer + value pairs)
  iVar3 = 5;
  do {
    if (*piVar4 != 0) {
      FUN_004daf90(piVar4); // Free memory at pointer
      *piVar4 = 0;
    }
    piVar4 = piVar4 + 2; // Step by 8 bytes
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  
  // Reset specific message type tracking entries
  this[0x91] = 0; // +0x244
  this[0x93] = 0; // +0x24C
  this[0xab] = 0; // +0x2AC
  this[0x8f] = 0; // +0x23C
  this[0x95] = 0; // +0x254
  this[0x9d] = 0; // +0x274
  this[0x9b] = 0; // +0x26C
  this[0x97] = 0; // +0x25C
  this[0xa3] = 0; // +0x28C
  this[0xa5] = 0; // +0x294
  
  // Register pressure message name for player breaking destructibles
  FUN_00408240(&DAT_0112a588,"iMsgPressurePlayerBreakingDestructibles");
  
  // If global message table is present, connect our function table to it
  if (DAT_0120e93c != 0) {
    FUN_00408900(this + 0xf, &DAT_0120e93c, 0x8000);
  }
  
  this[0x8e] = this; // +0x238 - self-reference
  
  return this;
}