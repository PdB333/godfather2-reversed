// FUNC_NAME: GodfatherGameManager::constructor
undefined4 * __fastcall GodfatherGameManager::constructor(undefined4 *this)
{
  undefined1 *allocatedBuffer;
  
  FUN_005bf9b0(); // likely base class constructor or engine init
  this[0x13] = &PTR_LAB_00d88730; // vtable or interface pointer +0x4C
  DAT_011304f8 = this; // global singleton pointer
  *this = &PTR_FUN_00d88760; // vtable pointer
  this[4] = &PTR_LAB_00d88738; // +0x10
  this[0x13] = &PTR_LAB_00d88734; // +0x4C
  this[0x14] = 1; // +0x50 - some flag or count
  this[0x15] = 0xffffffff; // +0x54 - invalid/initial value
  this[0x16] = 0; // +0x58
  this[0x17] = 0; // +0x5C
  this[0x18] = 0; // +0x60
  *(undefined1 *)(this + 0x19) = 0; // +0x64 - byte
  this[0x1a] = 0; // +0x68
  this[0x1b] = &PTR_LAB_00d83b18; // +0x6C - pointer to static data
  this[0x3c] = 0; // +0xF0
  this[0x3d] = 0; // +0xF4
  this[0x3e] = 0; // +0xF8
  this[0x3f] = 0; // +0xFC
  this[0x40] = 0; // +0x100
  this[0x46] = 0; // +0x118
  this[0x47] = 0; // +0x11C
  this[0x48] = 0; // +0x120
  this[0x49] = 0; // +0x124
  this[0x4a] = 0; // +0x128
  this[0x4b] = 0; // +0x12C
  this[0x4c] = 0; // +0x130
  this[0x4d] = 0; // +0x134
  this[0x4e] = 0; // +0x138
  this[0x4f] = 0; // +0x13C
  this[0x50] = 0; // +0x140
  this[0x51] = 0; // +0x144
  this[0x52] = 0; // +0x148
  this[0x53] = 0; // +0x14C
  this[0x54] = 0; // +0x150
  *(undefined1 *)(this + 0x5f) = 0; // +0x17C - byte
  this[0x60] = 0; // +0x180
  *(undefined1 *)(this + 0x61) = 0; // +0x184 - byte
  *(undefined1 *)((int)this + 0x185) = 0; // +0x185 - byte
  *(undefined1 *)((int)this + 0x186) = 0; // +0x186 - byte
  allocatedBuffer = (undefined1 *)FUN_009c8e80(0x80); // allocate 128 bytes
  this[0x41] = allocatedBuffer; // +0x104
  *allocatedBuffer = 0;
  allocatedBuffer = (undefined1 *)FUN_009c8e80(0x80);
  this[0x42] = allocatedBuffer; // +0x108
  *allocatedBuffer = 0;
  allocatedBuffer = (undefined1 *)FUN_009c8e80(0x80);
  this[0x43] = allocatedBuffer; // +0x10C
  *allocatedBuffer = 0;
  allocatedBuffer = (undefined1 *)FUN_009c8e80(0x10);
  this[0x44] = allocatedBuffer; // +0x110
  *allocatedBuffer = 0;
  allocatedBuffer = (undefined1 *)FUN_009c8e80(0x10);
  this[0x45] = allocatedBuffer; // +0x114
  *allocatedBuffer = 0;
  *(undefined8 *)(this + 0x55) = 0; // +0x154 - 8 bytes
  *(undefined8 *)(this + 0x57) = 0; // +0x15C - 8 bytes
  this[0x59] = 0; // +0x164
  *(undefined8 *)(this + 0x5a) = 0; // +0x168 - 8 bytes
  *(undefined8 *)(this + 0x5c) = 0; // +0x170 - 8 bytes
  this[0x5e] = 0; // +0x178
  return this;
}