// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, undefined4 param_2)
{
  undefined4 uVar1;
  
  // Call base class constructor
  FUN_008ded10(param_2);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d7fa20;
  
  // Initialize various virtual function table pointers (likely for different interfaces or states)
  this[0xf] = &PTR_LAB_00d7fa10;
  this[0x12] = &PTR_LAB_00d7fa0c;
  this[0x14] = &PTR_LAB_00d7fa08;
  this[0x15] = &PTR_LAB_00d7f9a8;
  this[0x16] = &PTR_LAB_00d7f940;
  
  // Call FUN_008de480 with scale/default values (1.0f for each component)
  FUN_008de480(0, 0, 0, 0x3f800000, 0x3f800000, 0x3f800000);
  
  // Initialize member variables
  this[0x8d] = 0;                                    // +0x234: some flag/counter
  uVar1 = _DAT_00d5780c;                               // Global data used for initialization
  this[0x8b] = 1;                                     // +0x22c: initial value 1
  this[0x8c] = 0xffffffff;                            // +0x230: set to -1 (invalid index/ID)
  this[0x8e] = uVar1;                                 // +0x238: copy from global
  *(undefined1 *)(this + 0x8f) = 0;                   // +0x23c: byte set to 0
  this[0x90] = 0;                                     // +0x240: zero
  *(undefined1 *)(this + 0x91) = 0;                   // +0x244: byte set to 0
  this[0x92] = 0;                                     // +0x248: zero
  *(undefined2 *)(this + 0x93) = 0;                   // +0x24c: word set to 0
  *(undefined2 *)((int)this + 0x24e) = 0;             // +0x24e: word set to 0 (partial offset)
  this[0x94] = 0;                                     // +0x250: zero
  *(undefined2 *)(this + 0x95) = 0;                   // +0x254: word set to 0
  *(undefined2 *)((int)this + 0x256) = 0;             // +0x256: word set to 0
  this[0x96] = 0;                                     // +0x258: zero
  *(undefined2 *)(this + 0x97) = 0;                   // +0x25c: word set to 0
  *(undefined2 *)((int)this + 0x25e) = 0;             // +0x25e: word set to 0
  this[0x98] = 0;                                     // +0x260: zero
  *(undefined2 *)(this + 0x99) = 0;                   // +0x264: word set to 0
  *(undefined2 *)((int)this + 0x266) = 0;             // +0x266: word set to 0
  
  // Additional initialization call
  FUN_00481530();
  
  return this;
}