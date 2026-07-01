// FUNC_NAME: GodfatherGameManager::constructor
undefined4 * __thiscall GodfatherGameManager::constructor(undefined4 *this, undefined4 param_2)
{
  FUN_0046c590(param_2);
  *this = &PTR_FUN_00d69cd4;
  this[0xf] = &PTR_LAB_00d69cc4;  // +0x3C - vtable or function pointer
  this[0x12] = &PTR_LAB_00d69cc0; // +0x48 - vtable or function pointer
  this[0x17] = 0;                 // +0x5C - some pointer
  this[0x18] = 0;                 // +0x60 - some pointer
  this[0x19] = 0;                 // +0x64 - some pointer
  this[0x1a] = 0;                 // +0x68 - some pointer
  this[0x1b] = 0;                 // +0x6C - some pointer
  this[0x1c] = 0;                 // +0x70 - some pointer
  this[0x1d] = 0;                 // +0x74 - some pointer
  this[0x1e] = 0;                 // +0x78 - some pointer
  this[0x22] = 0;                 // +0x88 - some pointer
  this[0x21] = 0;                 // +0x84 - some pointer
  this[0x20] = 0;                 // +0x80 - some pointer
  this[0x1f] = 0;                 // +0x7C - some pointer
  this[0x23] = 2;                 // +0x8C - some integer (default 2)
  this[0x24] = 2;                 // +0x90 - some integer (default 2)
  this[0x25] = 2;                 // +0x94 - some integer (default 2)
  this[0x26] = 2;                 // +0x98 - some integer (default 2)
  this[0x27] = 0;                 // +0x9C - some integer
  this[0x28] = 0;                 // +0xA0 - some integer
  this[0x29] = 0;                 // +0xA4 - some integer
  this[0x2a] = 0;                 // +0xA8 - some integer
  this[0x2b] = 0;                 // +0xAC - some integer
  this[0x2c] = 0;                 // +0xB0 - some integer
  this[0x2d] = 0;                 // +0xB4 - some integer
  this[0x2e] = 0;                 // +0xB8 - some integer
  this[0x2f] = 0;                 // +0xBC - some integer
  this[0x30] = 0;                 // +0xC0 - some integer
  this[0x31] = 0;                 // +0xC4 - some integer
  this[0x32] = 0;                 // +0xC8 - some integer
  this[0x33] = 0;                 // +0xCC - some integer
  this[0x34] = 0;                 // +0xD0 - some integer
  this[0x35] = 0;                 // +0xD4 - some integer
  this[0x36] = 0;                 // +0xD8 - some integer
  this[0x37] = 0;                 // +0xDC - some integer
  this[0x16] = 0;                 // +0x58 - some pointer
  this[0x15] = 0;                 // +0x54 - some pointer
  this[0x14] = 0;                 // +0x50 - some pointer
  if (DAT_0120e93c != 0) {
    FUN_00408900(this + 0xf, &DAT_0120e93c, 0x8000); // copy 0x8000 bytes from global data
  }
  return this;
}