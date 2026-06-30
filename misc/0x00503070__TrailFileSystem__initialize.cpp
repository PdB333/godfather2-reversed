// FUNC_NAME: TrailFileSystem::initialize
undefined * FUN_00503070(void)

{
  // Initialize trail file system globals
  // +0x00: pointer to vtable or function table
  _DAT_01219130 = &PTR_LAB_00e37e60;
  
  // +0x04: file extension string pointer
  _DAT_01219134 = "Trail";
  
  // +0x08: file extension as 4-byte integer (".trl" in little-endian)
  _DAT_01219138 = 0x2e74726c;
  
  // +0x0c: version or size field
  _DAT_0121913c = 0;
  
  // +0x10: some count or flag
  _DAT_01219140 = 6;
  
  // +0x14: another pointer or handle
  _DAT_01219144 = 0;
  
  // +0x18: buffer size (0x800 = 2048 bytes)
  _DAT_01219148 = 0x800;
  
  // +0x1c: another pointer or handle
  _DAT_0121914c = 0;
  
  // +0x20: another pointer or handle
  _DAT_01219150 = 0;
  
  // +0x24: another pointer or handle
  _DAT_01219154 = 0;
  
  // Return pointer to the trail file system object
  return &DAT_01219130;
}