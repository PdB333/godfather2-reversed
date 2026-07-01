// FUNC_NAME: GameSession::GameSession
undefined4 * __thiscall GameSession::GameSession(undefined4 *this, undefined4 someParam)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  // Call base class constructor
  BaseClass::BaseClass(someParam);
  
  // Set up vtable pointers (multiple inheritance)
  this[0x14] = &PTR_LAB_00d5e214;  // +0x50: first vtable pointer (overwritten later)
  *this = &PTR_FUN_00d803fc;       // +0x00: primary vtable
  this[0xf] = &PTR_LAB_00d803ec;   // +0x3c: secondary vtable
  this[0x12] = &PTR_LAB_00d803e8;  // +0x48: tertiary vtable
  this[0x14] = &PTR_LAB_00d803d0;  // +0x50: final vtable (overwrites previous)
  
  // Initialize member fields with sentinel debug markers
  this[0x15] = 0;                  // +0x54
  *(undefined2 *)(this + 0x16) = 0; // +0x58 (2 bytes)
  *(undefined2 *)((int)this + 0x5a) = 0; // +0x5a (2 bytes)
  this[0x17] = 0;                  // +0x5c
  *(undefined2 *)(this + 0x18) = 0; // +0x60
  *(undefined2 *)((int)this + 0x62) = 0; // +0x62
  this[0x19] = 0xbadbadba;         // +0x64: debug sentinel
  this[0x1b] = 0xeac15a55;         // +0x6c
  this[0x1a] = 0xbeefbeef;         // +0x68
  this[0x1c] = 0x91100911;         // +0x70
  this[0x1f] = 0xeac15a55;         // +0x7c
  this[0x1d] = 0xbadbadba;         // +0x74
  this[0x1e] = 0xbeefbeef;         // +0x78
  this[0x20] = 0x91100911;         // +0x80
  this[0x21] = 0;                  // +0x84
  
  // Initialize two arrays of 0x17 dwords each (sub-structures)
  puVar2 = this + 0x22;            // +0x88: start of first array
  puVar1 = this + 0x28;            // +0xa0: start of second array
  iVar3 = 2;
  do {
    *puVar2 = 0xbadbadba;          // first element of first array
    // Initialize second array elements (relative to puVar1)
    puVar1[-5] = 0xbeefbeef;
    puVar1[-4] = 0xeac15a55;
    puVar1[-3] = 0x91100911;
    puVar1[-2] = 0xbadbadba;
    puVar1[-1] = 0xbeefbeef;
    *puVar1 = 0xeac15a55;
    puVar1[1] = 0x91100911;
    puVar1[2] = 0xbadbadba;
    puVar1[3] = 0xbeefbeef;
    puVar1[4] = 0xeac15a55;
    puVar1[5] = 0x91100911;
    puVar1[6] = 0;
    *(undefined2 *)(puVar1 + 7) = 0;
    *(undefined2 *)((int)puVar1 + 0x1e) = 0;
    puVar1[8] = 0;
    puVar1[9] = 0;
    puVar1[10] = 0;
    puVar1[0xb] = 0;
    puVar1[0xc] = 0;
    puVar2 = puVar2 + 0x17;        // advance by 0x5c bytes
    puVar1 = puVar1 + 0x17;
    iVar3 = iVar3 + -1;
  } while (-1 < iVar3);
  
  // Initialize remaining fields
  this[0x67] = 0;                  // +0x19c
  *(undefined2 *)(this + 0x68) = 0; // +0x1a0
  *(undefined2 *)((int)this + 0x1a2) = 0; // +0x1a2
  *(undefined1 *)(this + 0x69) = 0; // +0x1a4
  *(undefined1 *)((int)this + 0x1a5) = 0; // +0x1a5
  this[0x6a] = 0;                  // +0x1a8
  this[0x6b] = 0;                  // +0x1ac
  *(undefined2 *)(this + 0x6c) = 0; // +0x1b0
  *(undefined2 *)((int)this + 0x1b2) = 0; // +0x1b2
  this[0x6d] = 0;                  // +0x1b4
  *(undefined2 *)(this + 0x6e) = 0; // +0x1b8
  *(undefined2 *)((int)this + 0x1ba) = 0; // +0x1ba
  this[0x6f] = 0;                  // +0x1bc
  *(undefined2 *)(this + 0x70) = 0; // +0x1c0
  *(undefined2 *)((int)this + 0x1c2) = 0; // +0x1c2
  this[0x71] = 0;                  // +0x1c4
  this[0x72] = 0;                  // +0x1c8
  this[0x73] = 0xbadbadba;         // +0x1cc
  this[0x74] = 0xbeefbeef;         // +0x1d0
  this[0x75] = 0xeac15a55;         // +0x1d4
  this[0x76] = 0x91100911;         // +0x1d8
  this[0x77] = 0xffffffff;         // +0x1dc
  this[0x78] = 0;                  // +0x1e0
  *(undefined2 *)(this + 0x79) = 0; // +0x1e4
  *(undefined2 *)((int)this + 0x1e6) = 0; // +0x1e6
  this[0x7a] = 0;                  // +0x1e8
  *(undefined2 *)(this + 0x7b) = 0; // +0x1ec
  *(undefined2 *)((int)this + 0x1ee) = 0; // +0x1ee
  this[0x7c] = 0;                  // +0x1f0
  *(undefined2 *)(this + 0x7d) = 0; // +0x1f4
  *(undefined2 *)((int)this + 0x1f6) = 0; // +0x1f6
  this[0x7e] = 0;                  // +0x1f8
  this[0x7f] = 0;                  // +0x1fc
  this[0x80] = 0;                  // +0x200
  *(undefined2 *)(this + 0x81) = 0; // +0x204
  *(undefined2 *)((int)this + 0x206) = 0; // +0x206
  this[0x82] = 0;                  // +0x208
  *(undefined2 *)(this + 0x83) = 0; // +0x20c
  *(undefined2 *)((int)this + 0x20e) = 0; // +0x20e
  this[0x84] = 0;                  // +0x210
  *(undefined2 *)(this + 0x85) = 0; // +0x214
  *(undefined2 *)((int)this + 0x216) = 0; // +0x216
  this[0x86] = 0;                  // +0x218
  this[0x87] = 0;                  // +0x21c
  this[0x88] = 0;                  // +0x220
  *(undefined2 *)(this + 0x89) = 0; // +0x224
  *(undefined2 *)((int)this + 0x226) = 0; // +0x226
  this[0x8a] = 0;                  // +0x228
  *(undefined2 *)(this + 0x8b) = 0; // +0x22c
  *(undefined2 *)((int)this + 0x22e) = 0; // +0x22e
  this[0x8c] = 0;                  // +0x230
  *(undefined2 *)(this + 0x8d) = 0; // +0x234
  *(undefined2 *)((int)this + 0x236) = 0; // +0x236
  this[0x8e] = 0;                  // +0x238
  this[0x8f] = 0;                  // +0x23c
  this[0x35] = 0;                  // +0xd4
  this[0x4c] = 0;                  // +0x130
  this[99] = 0;                    // +0x18c (0x63*4)
  
  // Copy initial data buffer if available
  if (g_initialDataBuffer != 0) {
    memcpy(this + 0xf, g_initialDataBuffer, 0x8000); // +0x3c: copy 32KB
  }
  
  return this;
}