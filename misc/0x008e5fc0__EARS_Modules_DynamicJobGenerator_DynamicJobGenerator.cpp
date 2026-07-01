// Xbox PDB: EARS_Modules_DynamicJobGenerator_DynamicJobGenerator
// FUNC_NAME: DynamicJobGenerator::constructor
undefined4 * __fastcall DynamicJobGenerator::constructor(undefined4 *this)
{
  undefined4 *puVar1;
  
  DAT_0112a670 = this;
  this[1] = &PTR_FUN_00e2f19c;  // vtable pointer
  this[3] = 0;                   // +0x0C: some state
  puVar1 = this + 1;
  this[2] = 1;                   // +0x08: enabled flag
  this[4] = &PTR_LAB_00e30fe0;  // +0x10: another vtable or callback
  *this = &PTR_FUN_00d8051c;    // +0x00: vtable
  *puVar1 = &PTR_LAB_00d8050c;  // +0x04: vtable
  this[4] = &PTR_LAB_00d804fc;  // +0x10: vtable
  this[5] = 0;                  // +0x14: job list pointer
  this[6] = 0;                  // +0x18: job count
  this[7] = 0;                  // +0x1C: 
  this[8] = 0;                  // +0x20: 
  this[9] = 0;                  // +0x24: 
  this[10] = 0;                 // +0x28: 
  this[0xb] = 0;                // +0x2C: 
  this[0xc] = 0;                // +0x30: 
  this[0xd] = 0;                // +0x34: 
  this[0xe] = 0;                // +0x38: 
  this[0xf] = 0;                // +0x3C: 
  this[0x10] = 0;               // +0x40: 
  this[0x11] = 0;               // +0x44: 
  this[0x12] = 0;               // +0x48: 
  this[0x13] = 0;               // +0x4C: 
  this[0x14] = 0;               // +0x50: 
  this[0x15] = 0;               // +0x54: 
  this[0x16] = 0;               // +0x58: 
  this[0x17] = 0;               // +0x5C: 
  this[0x18] = 0;               // +0x60: 
  *(undefined1 *)(this + 0x19) = 1;  // +0x64: byte flag
  this[0x1a] = 0;               // +0x68: 
  FUN_00463980(0xc8ed3b85, this + 4, 1);  // register message handler
  FUN_008e5cf0(0x20);           // allocate 0x20 bytes (32)
  if (DAT_012069c4 != 0) {
    FUN_00408900(puVar1, &DAT_012069c4, 0x8000);  // subscribe to message
  }
  FUN_00408240(&DAT_0112fdb0, "iMsgEnableDynamicJobGenerator");
  if (DAT_0112fdb0 != 0) {
    FUN_00408900(puVar1, &DAT_0112fdb0, 0x8000);  // subscribe to enable message
  }
  FUN_00408240(&DAT_0112fdb8, "iMsgDisableDynamicJobGenerator");
  if (DAT_0112fdb8 != 0) {
    FUN_00408900(puVar1, &DAT_0112fdb8, 0x8000);  // subscribe to disable message
  }
  FUN_00408240(&DAT_0112fdc0, "iMsgDynamicJobCompleted");
  return this;
}