// FUNC_NAME: LightManager::LightManager
undefined4 * __thiscall LightManager::LightManager(undefined4 *thisObj, undefined4 *allocator)

{
  void *buffer;
  undefined4 *localVar1;
  undefined4 result;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  // Store global pointer to this instance
  DAT_012233a4 = thisObj;
  
  // Initialize base class vtable pointers
  thisObj[0] = &PTR_FUN_00e31680;          // +0x00: first vtable
  thisObj[1] = &PTR_LAB_00e31684;          // +0x04: second vtable (overwrites previous assignment)
  thisObj[2] = 0;                          // +0x08: unknown
  
  // Set function pointer and allocate buffer for light data
  thisObj[0x14] = &LAB_004aa160;           // +0x50: function pointer
  thisObj[0x15] = 0x400;                   // +0x54: buffer element count (1024)
  buffer = (void *)FUN_009c8e80(0x1000);   // allocate 4096 bytes
  thisObj[0x16] = buffer;                  // +0x58: buffer pointer
  thisObj[0x17] = 0;                       // +0x5C: used count
  thisObj[0x18] = 0;                       // +0x60: unknown
  thisObj[0x19] = 0;                       // +0x64: unknown
  _memset(buffer, 0, thisObj[0x15] * 4);    // clear buffer
  thisObj[0x1a] = 0;                       // +0x68: initialize to zero
  thisObj[0x1b] = 0;                       // +0x6C: initialize to zero
  
  // Get some system values (likely frame counter or time)
  localVar1 = (undefined4 *)FUN_00450c20(&local_c);
  thisObj[0x1a] = *localVar1;             // +0x68: value A
  thisObj[0x1b] = localVar1[1];           // +0x6C: value B
  
  // Ensure allocator is valid
  if (allocator == (undefined4 *)0x0) {
    allocator = (undefined4 *)FUN_009c8f80(); // get default allocator
  }
  
  // Set various size/capacity parameters
  thisObj[6] = DAT_00e39f98;               // +0x18: max lights?
  thisObj[7] = DAT_00e2fc48;               // +0x1C: unknown
  thisObj[4] = 0;                          // +0x10: current count
  thisObj[5] = 0x14;                       // +0x14: light projection size? (20)
  thisObj[0xb] = 0x800;                    // +0x2C: shadow map size? (2048)
  thisObj[8] = 0xffffffff;                 // +0x20: -1
  thisObj[9] = 0xffffffff;                 // +0x24: -1
  thisObj[0xc] = 0;                        // +0x30: unknown
  
  // Allocate light data via allocator interface
  local_c = 2;
  local_8 = 4;
  local_4 = 0;
  result = (**(code **)*allocator)(0x4000, &local_c);  // allocate 16384 bytes
  thisObj[10] = result;                    // +0x28: light buffer?
  
  local_c = 0;
  result = (**(code **)*allocator)(thisObj[5] * thisObj[5] * 4, &stack0xffffffec); // allocate 20*20*4 = 1600 bytes
  thisObj[0xd] = result;                   // +0x34: projection data?
  
  // Zero out additional fields
  thisObj[0x10] = 0;                       // +0x40
  thisObj[0x11] = 0;                       // +0x44
  thisObj[0x12] = 0;                       // +0x48
  thisObj[0x13] = 0;                       // +0x4C
  
  // Register light table of contents
  FUN_0049c6e0("LightTOC", 1);
  
  // Post-initialization
  FUN_00450950();
  
  return thisObj;
}