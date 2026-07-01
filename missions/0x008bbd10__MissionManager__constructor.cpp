// FUNC_NAME: MissionManager::constructor
undefined4 * __thiscall MissionManager::constructor(undefined4 *this, undefined4 param_2)
{
  undefined4 uVar1;
  
  FUN_008ba220(param_2);  // base class constructor
  *this = &PTR_FUN_00d7bac0;  // vtable pointer
  // Mission specific vtable entries at various offsets
  this[0xf] = &PTR_LAB_00d7bab0;   // +0x3C
  this[0x12] = &PTR_LAB_00d7baac;  // +0x48
  this[0x14] = &PTR_LAB_00d7baa8;  // +0x50
  this[0x15] = &PTR_LAB_00d7ba48;  // +0x54
  this[0x16] = &PTR_LAB_00d7b9e0;  // +0x58
  this[0x60] = &PTR_LAB_00d7b9c8;  // +0x180
  // Magic number markers for object validation
  this[0xa4] = 0xbadbadba;   // +0x290
  this[0xa5] = 0xbeefbeef;   // +0x294
  this[0xa6] = 0xeac15a55;   // +0x298 - "EA C1 A5 55" string
  this[0xa7] = 0x91100911;   // +0x29C
  this[0xa8] = 0;            // +0x2A0
  uVar1 = _DAT_00d5c458;     // global mission data pointer
  this[0xa9] = 0;            // +0x2A4
  this[0xaa] = 0;            // +0x2A8
  *(undefined1 *)(this + 0xac) = 0;   // +0x2B0 low byte
  *(undefined1 *)((int)this + 0x2b1) = 0;  // +0x2B1
  *(undefined2 *)((int)this + 0x2b2) = 0;  // +0x2B2 short
  this[0xab] = uVar1;        // +0x2AC - store global mission data
  // Clear magic number markers
  this[0xa7] = 0;            // +0x29C
  this[0xa6] = 0;            // +0x298
  this[0xa5] = 0;            // +0x294
  this[0xa4] = 0;            // +0x290
  return this;
}