// FUNC_NAME: GodfatherGameManager::constructor
undefined4 * __fastcall GodfatherGameManager::constructor(undefined4 *this)
{
  undefined1 *puVar1;
  
  // Call base class constructor (likely EARSObject or similar)
  FUN_00957ed0();
  
  // Set vtable pointer (offset +0x50 = 0x14 * 4)
  this[0x14] = &PTR_LAB_00d8fe58;
  
  // Store singleton instance pointer
  DAT_0112fee4 = this;
  
  // Set vtable pointer (offset 0x0)
  *this = &PTR_FUN_00d8fe88;
  
  // Set additional vtable pointers
  this[4] = &PTR_LAB_00d8fe60;      // +0x10
  this[0x14] = &PTR_LAB_00d8fe5c;   // +0x50
  
  // Initialize member variables to 0
  this[0x15] = 0;   // +0x54
  this[0x16] = 0;   // +0x58
  this[0x17] = 0;   // +0x5C
  this[0x18] = 0;   // +0x60
  this[0x19] = 0;   // +0x64
  
  // Initialize to -1 (invalid/not set)
  this[0x1a] = 0xffffffff;  // +0x68
  this[0x1b] = 0xffffffff;  // +0x6C
  
  // Set pointer to some data structure
  this[0x1c] = &PTR_LAB_00d8fe4c;  // +0x70
  this[0x2d] = &PTR_LAB_00d8fe4c;  // +0xB4
  
  // Initialize more fields to 0
  this[0x40] = 0;   // +0x100
  this[0x41] = 0;   // +0x104
  this[0x42] = 0;   // +0x108
  this[0x43] = 0;   // +0x10C
  this[0x44] = 0;   // +0x110
  this[0x45] = 0;   // +0x114
  this[0x46] = 0;   // +0x118
  this[0x47] = 0;   // +0x11C
  this[0x48] = 0;   // +0x120
  this[0x49] = 0;   // +0x124
  
  // Initialize byte fields to 0
  *(undefined1 *)(this + 0x4a) = 0;        // +0x128
  *(undefined1 *)((int)this + 0x129) = 0;  // +0x129
  *(undefined1 *)((int)this + 0x12a) = 0;  // +0x12A
  *(undefined1 *)((int)this + 299) = 0;    // +0x12B
  *(undefined1 *)(this + 0x4b) = 0;        // +0x12C
  *(undefined1 *)((int)this + 0x12d) = 0;  // +0x12D
  
  // Initialize to -1
  this[0x4c] = 0xffffffff;  // +0x130
  
  // Initialize to 0
  this[0x4d] = 0;  // +0x134
  
  // Allocate 0x40 bytes for a buffer
  puVar1 = (undefined1 *)FUN_009c8e80(0x40);
  this[0x3e] = puVar1;  // +0xF8
  *puVar1 = 0;
  
  // Allocate 0x100 bytes for another buffer
  puVar1 = (undefined1 *)FUN_009c8e80(0x100);
  this[0x3f] = puVar1;  // +0xFC
  *puVar1 = 0;
  
  return this;
}