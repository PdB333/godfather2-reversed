// Xbox PDB: EARS_Modules_PlayerGrappleSM_PlayerGrappleSM
// FUNC_NAME: PlayerF2FSM::constructor
undefined4 * __thiscall PlayerF2FSM_constructor(undefined4 *this, undefined4 param_2, undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  // Call base class constructor (likely FSM base)
  FUN_007ab5e0(param_2,param_3);
  *this = &PTR_LAB_00d6bfa8;  // vtable pointer
  // Initialize state machine variables
  this[0x1d] = 0xffffffff;  // +0x74 - previous state
  this[0x1e] = 0xffffffff;  // +0x78 - current state
  this[0x1f] = 0xffffffff;  // +0x7c - next state
  FUN_0081a870();  // Some initialization function
  // Clear various state flags and timers
  this[0x5d] = 0;  // +0x174
  this[0x5e] = 0;  // +0x178
  this[0x5f] = 0;  // +0x17c
  this[0x60] = 0;  // +0x180
  *(undefined2 *)(this + 0x61) = 0;  // +0x184 (2 bytes)
  this[0x62] = 0;  // +0x188
  this[99] = 0;    // +0x18c
  *(undefined1 *)(this + 0x66) = 0;  // +0x198 (1 byte)
  uVar2 = FUN_009c8e80(4);  // Allocate 4 bytes
  this[0x67] = uVar2;  // +0x19c - allocated pointer
  this[0x68] = 1;      // +0x1a0
  this[0x69] = 0;      // +0x1a4
  this[0x6a] = 0;      // +0x1a8
  *(undefined1 *)(this + 0x6b) = 0;  // +0x1ac (1 byte)
  this[0x6c] = 2;      // +0x1b0
  this[0x6f] = 0;      // +0x1bc
  this[0x70] = 1;      // +0x1c0
  *(undefined1 *)(this + 0x66) = 0;  // +0x198 - reset byte
  // Register for input messages
  FUN_007f6420(0x3a);  // Register for message 0x3a (likely pummel start)
  FUN_007f6420(0x3b);  // Register for message 0x3b (likely pummel end)
  // Get some global values
  iVar3 = FUN_007ab130();
  this[0x6d] = *(undefined4 *)(iVar3 + 4);  // +0x1b4
  iVar3 = FUN_007ab150();
  this[0x6e] = *(undefined4 *)(iVar3 + 4);  // +0x1b8
  FUN_007f63e0(6);  // Set some flag
  // Check if we need to set flag again
  if ((*(int *)(this[0x16] + 0xff0) != 0) && (*(int *)(this[0x16] + 0xff0) != 0x48)) {
    FUN_007f63e0(6);
  }
  // Handle debug/cheat mode
  FUN_00550c10(_DAT_00d5c458);
  cVar1 = FUN_00481660();
  if ((cVar1 != '\0') || (cVar1 = FUN_00481640(), cVar1 != '\0')) {
    FUN_00472130(0);  // Enable debug mode
  }
  // Initialize more state variables
  this[100] = 0xffffffff;   // +0x190
  this[0x65] = 0xffffffff;  // +0x194
  // Register message handlers
  FUN_00408240(&DAT_0112b9e8,"iMsgPummelStart");
  FUN_00408240(&DAT_0112b9f4,"iMsgPummelEnd");
  FUN_00408240(&DAT_0112b9e0,"iMsgExecutionStart");
  FUN_00408240(&DAT_0112b9fc,"iMsgExecutionEnd");
  // Initialize more state variables
  this[0x71] = 0;  // +0x1c4
  this[0x72] = 0;  // +0x1c8
  this[0x76] = 0;  // +0x1d8
  this[0x77] = 0;  // +0x1dc
  this[0x78] = 0;  // +0x1e0
  this[0x73] = 0;  // +0x1cc
  this[0x74] = 0;  // +0x1d0
  this[0x75] = 0;  // +0x1d4
  this[0x79] = 0;  // +0x1e4
  this[0x7a] = 0;  // +0x1e8
  return this;
}