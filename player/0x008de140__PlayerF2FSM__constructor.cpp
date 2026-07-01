// FUNC_NAME: PlayerF2FSM::constructor
undefined4 * __thiscall PlayerF2FSM_constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor (likely FSM base)
  FUN_008d8190(param_2);
  
  // Set vtable pointer (class hierarchy)
  *this = &PTR_FUN_00d7ea28;  // vtable for PlayerF2FSM
  
  // Initialize state machine function pointers
  this[0xf] = &PTR_LAB_00d7ea18;   // +0x3C - state function table entry
  this[0x12] = &PTR_LAB_00d7ea14;  // +0x48 - state function table entry
  this[0x14] = &PTR_LAB_00d7ea10;  // +0x50 - state function table entry
  this[0x15] = &PTR_LAB_00d7e9b0;  // +0x54 - state function table entry
  this[0x16] = &PTR_LAB_00d7e948;  // +0x58 - state function table entry
  
  // Initialize state variables
  *(undefined2 *)(this + 0x65) = 0;     // +0x194 - current state ID (short)
  *(undefined2 *)((int)this + 0x196) = 0; // +0x196 - previous state ID (short)
  this[100] = 0;                         // +0x190 - state timer (int)
  
  return this;
}