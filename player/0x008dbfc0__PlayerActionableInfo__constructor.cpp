// FUNC_NAME: PlayerActionableInfo::constructor
undefined4 * __thiscall PlayerActionableInfo::constructor(undefined4 *this, undefined4 param_2)
{
  undefined4 uVar1;
  
  // Call base class constructor (likely EARSObject or similar)
  FUN_008d8190(param_2);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d7e240;
  
  // Initialize various member pointers/offsets
  this[0xf] = &PTR_LAB_00d7e230;  // +0x3C - some vtable or function pointer
  this[0x12] = &PTR_LAB_00d7e22c; // +0x48
  this[0x14] = &PTR_LAB_00d7e228; // +0x50
  this[0x15] = &PTR_LAB_00d7e1c8; // +0x54
  this[0x16] = &PTR_LAB_00d7e160; // +0x58
  
  // Initialize various state fields to 0
  this[100] = 0;   // +0x190 - some integer state
  this[0x65] = 0;  // +0x194
  *(undefined2 *)(this + 0x66) = 0;  // +0x198 - short
  *(undefined2 *)((int)this + 0x19a) = 0; // +0x19A - short
  this[0x67] = 0;  // +0x19C
  *(undefined2 *)(this + 0x68) = 0;  // +0x1A0 - short
  *(undefined2 *)((int)this + 0x1a2) = 0; // +0x1A2 - short
  this[0x69] = 0;  // +0x1A4
  *(undefined2 *)(this + 0x6a) = 0;  // +0x1A8 - short
  *(undefined2 *)((int)this + 0x1aa) = 0; // +0x1AA - short
  this[0x6b] = 0;  // +0x1AC
  
  // Initialize some default values from global data
  this[0x6d] = DAT_00d5ef70;  // +0x1B4 - some default value
  uVar1 = DAT_00d5f00c;
  this[0x6c] = 0;  // +0x1B0
  this[0x6e] = uVar1;  // +0x1B8 - another default value
  
  // Clear a block of 16 fields (likely an array or struct)
  this[0x73] = 0;  // +0x1CC
  this[0x74] = 0;  // +0x1D0
  this[0x75] = 0;  // +0x1D4
  this[0x76] = 0;  // +0x1D8
  this[0x77] = 0;  // +0x1DC
  this[0x78] = 0;  // +0x1E0
  this[0x79] = 0;  // +0x1E4
  this[0x7a] = 0;  // +0x1E8
  this[0x7b] = 0;  // +0x1EC
  this[0x7c] = 0;  // +0x1F0
  this[0x7d] = 0;  // +0x1F4
  this[0x7e] = 0;  // +0x1F8
  this[0x7f] = 0;  // +0x1FC
  this[0x80] = 0;  // +0x200
  this[0x81] = 0;  // +0x204
  
  // Call some initialization function
  FUN_00481530();
  
  // Re-zero some fields (likely redundant or re-initialized)
  this[0x69] = 0;  // +0x1A4
  this[0x65] = 0;  // +0x194
  this[0x67] = 0;  // +0x19C
  
  return this;
}