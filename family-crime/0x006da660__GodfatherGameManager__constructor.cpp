// FUNC_NAME: GodfatherGameManager::constructor
undefined4 * __thiscall GodfatherGameManager::constructor(undefined4 *this, undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  // Call base class constructor
  FUN_00473d90(param_2);
  
  // Load global data values
  uVar1 = DAT_00d5efd0;
  uVar2 = DAT_00d5e288;
  
  // Set vtable pointer at +0x00
  *this = &PTR_FUN_00d5f610;
  
  // Initialize various member fields with function pointers and data
  // +0x3C (0xF * 4)
  this[0xf] = &PTR_LAB_00d5f600;
  // +0x48 (0x12 * 4)
  this[0x12] = &PTR_LAB_00d5f5fc;
  // +0x50 (0x14 * 4)
  this[0x14] = &PTR_LAB_00d5f5f8;
  // +0x94 (0x25 * 4)
  this[0x25] = uVar2;
  // +0x98 (0x26 * 4)
  this[0x26] = uVar1;
  // +0x9C (0x27 * 4)
  this[0x27] = uVar2;
  // +0xA0 (0x28 * 4)
  this[0x28] = uVar1;
  
  uVar1 = _DAT_00d5780c;
  // +0xA8 (0x2A * 4)
  this[0x2a] = uVar2;
  uVar2 = DAT_00e446dc;
  // +0xA4 (0x29 * 4)
  this[0x29] = uVar1;
  // +0xAC (0x2B * 4)
  this[0x2b] = uVar2;
  // +0xB0 (0x2C * 4)
  this[0x2c] = uVar1;
  // +0xB4 (0x2D * 4)
  this[0x2d] = uVar1;
  
  // +0x54 (0x15 * 4)
  this[0x15] = DAT_00d5f5f0;
  // +0x58 (0x16 * 4)
  this[0x16] = DAT_00d5f5f4;
  
  return this;
}