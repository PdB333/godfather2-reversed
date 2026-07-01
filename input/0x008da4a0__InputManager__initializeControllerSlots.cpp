// FUNC_NAME: InputManager::initializeControllerSlots
undefined4 * __thiscall FUN_008da4a0(undefined4 *this, undefined4 param_2)
{
  undefined4 uVar1;
  
  // Call base class constructor or initialization
  FUN_008d8190(param_2);
  
  // Set vtable pointer
  uVar1 = DAT_00d5d7b8;
  *this = &PTR_FUN_00d7df08;
  
  // Initialize controller slot pointers (16 slots, 0x44 bytes each)
  // Slot 0: +0x3C (0xF * 4)
  this[0xf] = &PTR_LAB_00d7def8;
  // Slot 1: +0x48 (0x12 * 4)
  this[0x12] = &PTR_LAB_00d7def4;
  // Slot 2: +0x50 (0x14 * 4)
  this[0x14] = &PTR_LAB_00d7def0;
  // Slot 3: +0x54 (0x15 * 4)
  this[0x15] = &PTR_LAB_00d7de90;
  // Slot 4: +0x58 (0x16 * 4)
  this[0x16] = &PTR_LAB_00d7de28;
  
  // Zero out controller state arrays (5 ints at +0x190 to +0x1A0)
  this[100] = 0;  // +0x190
  this[0x65] = 0; // +0x194
  this[0x66] = 0; // +0x198
  this[0x67] = 0; // +0x19C
  this[0x68] = 0; // +0x1A0
  
  // Zero out 16-bit values for controller axes/buttons
  // Each pair is a 16-bit value at specific offsets
  *(undefined2 *)(this + 0x6f) = 0;  // +0x1BC
  *(undefined2 *)((int)this + 0x1be) = 0;  // +0x1BE
  *(undefined2 *)(this + 0x71) = 0;  // +0x1C4
  *(undefined2 *)((int)this + 0x1c6) = 0;  // +0x1C6
  *(undefined2 *)(this + 0x73) = 0;  // +0x1CC
  *(undefined2 *)((int)this + 0x1ce) = 0;  // +0x1CE
  *(undefined2 *)(this + 0x75) = 0;  // +0x1D4
  *(undefined2 *)((int)this + 0x1d6) = 0;  // +0x1D6
  *(undefined2 *)(this + 0x77) = 0;  // +0x1DC
  *(undefined2 *)((int)this + 0x1de) = 0;  // +0x1DE
  
  // Zero out 32-bit values for controller state
  this[0x6e] = 0;  // +0x1B8
  this[0x70] = 0;  // +0x1C0
  this[0x72] = 0;  // +0x1C8
  this[0x74] = 0;  // +0x1D0
  this[0x76] = 0;  // +0x1D8
  
  // Set default values from global data
  this[0x6b] = uVar1;  // +0x1AC - default axis threshold
  this[0x6c] = uVar1;  // +0x1B0 - default axis threshold
  
  uVar1 = DAT_00d5d70c;
  this[0x6a] = 0;      // +0x1A8 - controller index
  this[0x69] = 1;      // +0x1A4 - enabled flag
  this[0x6d] = uVar1;  // +0x1B4 - default dead zone
  
  return this;
}