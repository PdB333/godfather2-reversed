// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
int* __thiscall GodfatherGameManager::GodfatherGameManager(int* this)
{
  int* pVtable;
  int baseClassPtr;
  int* piVar4;  // used for vtable swap pattern
  int iVar5;
  int iVar6;

  iVar5 = DAT_00d5d7b8;  // some global constant
  iVar6 = 0;

  // Initialize first sub-object (offset +0x18 to +0x2C)
  this[6] = 0;   // +0x18
  this[7] = 0;   // +0x1C
  this[8] = 0;   // +0x20
  this[9] = 0;   // +0x24
  this[0xE] = 0; // +0x38
  this[0xF] = 0; // +0x3C
  this[0x10] = 0;// +0x40
  *(byte*)(this + 0x11) = 0; // +0x44 byte
  this[0xB] = (int)&PTR_LAB_00d7006c; // vtable for first subobject (+0x2C)
  this[0x12] = (int)&PTR_LAB_00d7006c;// +0x48

  // Initialize second sub-object
  this[0x15] = 0;  // +0x54
  this[0x16] = 0;  // +0x58
  this[0x17] = 0;  // +0x5C
  *(byte*)(this + 0x18) = 0; // +0x60 byte
  this[0x19] = (int)&PTR_LAB_00d7006c; // vtable (+0x64)
  this[0x1C] = 0;  // +0x70
  this[0x1D] = 0;  // +0x74
  this[0x1E] = 0;  // +0x78
  *(byte*)(this + 0x1F) = 0; // +0x7C byte
  this[0x20] = (int)&PTR_LAB_00d7006c; // vtable (+0x80)

  // Initialize third sub-object
  this[0x23] = 0;  // +0x8C
  this[0x24] = 0;  // +0x90
  this[0x25] = 0;  // +0x94
  *(byte*)(this + 0x26) = 0; // +0x98 byte
  this[0x2A] = 0;  // +0xA8
  this[0x2B] = 0;  // +0xAC
  this[0x2C] = 0;  // +0xB0
  *(byte*)(this + 0x2D) = 0; // +0xB4 byte
  this[0x27] = (int)&PTR_LAB_00d70074; // vtable (+0x9C)
  this[0x2E] = (int)&PTR_LAB_00d70074; // +0xB8

  // Initialize fourth sub-object
  this[0x31] = 0;  // +0xC4
  this[0x32] = 0;  // +0xC8
  this[0x33] = 0;  // +0xCC
  *(byte*)(this + 0x34) = 0; // +0xD0 byte

  // Base class pointer initialization pattern (dual vtables)
  baseClassPtr = DAT_0112bb58;  // base address or singleton
  if (baseClassPtr != 0) {
    iVar3 = baseClassPtr;
  }
  else {
    iVar3 = 0;
  }
  pVtable = this + 1;           // first vtable pointer (+4)
  *this = iVar3;                // +0x00 base pointer

  piVar4 = this + 2;            // second vtable pointer slot (+8)
  *(byte*)(this + 0x178) = 0;  // +0x5E0 byte
  *(byte*)((int)this + 0x5E1) = 0;
  *(byte*)((int)this + 0x5E2) = 0;
  *(byte*)((int)this + 0x5E3) = 0;
  *(byte*)(this + 0x179) = 0;  // +0x5E4 byte
  *(byte*)((int)this + 0x5E5) = 0;

  this[0x3E] = iVar5;          // +0xF8 store constant
  *piVar4 = *pVtable;          // copy vtable
  this[0x3D] = 0;              // +0xF4
  this[10] = 0;                // +0x28
  *pVtable = (int)&DAT_00e53b50; // chain to global vtable

  FUN_007ef360();   // first sub-initializer (likely sets up vtable chain)

  // Repeat the base class vtable swap pattern
  iVar5 = 0;
  if (DAT_0112bb58 != 0) {
    iVar5 = DAT_0112bb58;
  }
  *this = iVar5;
  *piVar4 = *pVtable;
  if (piVar4 == (int*)0x0) {
    piVar4 = pVtable;
  }
  this[0x3D] = iVar6;
  this[10] = iVar6;
  *piVar4 = (int)&DAT_00e53b50;
  FUN_007ef360();   // second sub-initializer

  // Initialize more fields
  this[3] = 0;      // +0x0C
  this[4] = 0;      // +0x10
  this[5] = 0;      // +0x14
  FUN_007f0950();   // another sub-initializer

  // Set up size/capacity fields for sub-objects
  this[0xD] = *pVtable;  // +0x34
  this[0xC] = 0xB;       // +0x30 (size 11)
  this[0x14] = *pVtable; // +0x50
  this[0x13] = 0x11;     // +0x4C (size 17)
  this[0x1B] = *pVtable; // +0x6C
  this[0x1A] = 0x17;     // +0x68 (size 23)
  this[0x22] = *pVtable; // +0x88
  _DAT_00e53b80 = DAT_00d58cbc;   // static init
  this[0x21] = 0x1D;     // +0x84 (size 29)
  this[0x29] = *pVtable; // +0xA4
  this[0x28] = 0x1D;     // +0xA0 (size 29)
  this[0x30] = *pVtable; // +0xC0
  this[0x2F] = 0x1D;     // +0xBC (size 29)

  // Static/global configuration assignments
  this[0x17A] = DAT_01205220; // +0x5E8
  this[0x17B] = DAT_01205220; // +0x5EC
  _DAT_00e53b8c = DAT_00d5ddec;
  _DAT_00e53b90 = DAT_00d5842c;
  _DAT_00e53b94 = DAT_00d5c454;
  _DAT_00e53b98 = DAT_00d5f378;
  _DAT_00e53b9c = DAT_00d5ef6c;
  _DAT_00e53ba4 = _DAT_00d5c458;
  _DAT_00e53ba8 = DAT_00e448cc;
  _DAT_00e53bb8 = DAT_00e446c0;
  _DAT_00e53bbc = DAT_00e446c0;
  _DAT_00e53bd0 = DAT_00e446c0;
  _DAT_00e53bd4 = DAT_00e446c0;
  _DAT_00e53be8 = DAT_00e446c0;
  _DAT_00e53bec = DAT_00e446c0;
  _DAT_00e53bc0 = DAT_00d700d4;
  _DAT_00e53bc4 = DAT_00e44614;
  _DAT_00e53bd8 = DAT_00d700d4;
  _DAT_00e53bf0 = _DAT_00d69734;
  _DAT_00e53bc8 = DAT_00d5d934;
  _DAT_00e53bdc = DAT_00e44614;
  _DAT_00e53bf4 = DAT_00d5e288;
  _DAT_00e53b7c = 0;
  _DAT_00e53b84 = 0;
  _DAT_00e53b88 = DAT_00e445ac;
  _DAT_00e53ba0 = _DAT_00d5cf70;
  _DAT_00e53bac = DAT_00e445ac;
  _DAT_00e53bb0 = DAT_00e448a4;
  _DAT_00e53bb4 = _DAT_00d5780c;
  _DAT_00e53bcc = DAT_00d5d7b8;
  _DAT_00e53be0 = DAT_00e448a4;
  _DAT_00e53be4 = DAT_00d5ddec;
  _DAT_00e53bf8 = DAT_00d5efa4;
  _DAT_00e53c00 = DAT_00d5efa4;
  _DAT_00e53c04 = DAT_00d5efa4;
  _DAT_00e53c08 = DAT_00d5779c;
  _DAT_00e53c0c = DAT_00e44634;
  DAT_00e53c1c = DAT_00d5eee4;
  DAT_00e53c20 = DAT_00d620ac;
  _DAT_00e53c28 = DAT_00d6f444;
  _DAT_00e53c30 = DAT_00d5ccf8;
  _DAT_00e53c38 = DAT_00e44750;
  _DAT_00e53c60 = DAT_00e44750;
  _DAT_00e53c68 = DAT_00d5ef94;
  _DAT_00e53c6c = DAT_00d5ef94;
  _DAT_00e53c70 = DAT_00d5ef94;
  _DAT_00e53c74 = DAT_00e4475c;
  DAT_00e53c14 = DAT_00d5d7b8;
  DAT_00e53c18 = DAT_00d5d7b8;
  _DAT_00e53c78 = DAT_00d5f378;
  _DAT_00e53bfc = DAT_00d5f53c;
  DAT_00e53c10 = DAT_00e448a4;
  _DAT_00e53c24 = 0;
  _DAT_00e53c2c = _DAT_00d5780c;
  _DAT_00e53c34 = 0;
  _DAT_00e53c3c = 0;
  _DAT_00e53c40 = 0;
  _DAT_00e53c44 = 0;
  _DAT_00e53c48 = 0;
  _DAT_00e53c4c = 0;
  _DAT_00e53c50 = 0;
  _DAT_00e53c54 = 0;
  _DAT_00e53c58 = 0;
  _DAT_00e53c5c = DAT_00d700d0;
  _DAT_00e53c64 = DAT_00e445ac;
  _DAT_00e53c7c = 0;
  _DAT_00e53c80 = 0;
  _DAT_00e53c84 = DAT_00d5f520;
  _DAT_00e53c88 = _DAT_00d5cf70;
  _DAT_00e53c8c = _DAT_00d5cf70;
  _DAT_00e53c90 = 0;
  _DAT_00e53c94 = 0;
  _DAT_00e53c98 = 0;
  _DAT_00e53c9c = 0;
  _DAT_00e53ca0 = 0;
  _DAT_00e53ca4 = 0;
  _DAT_00e53ca8 = 0;
  _DAT_00e53cac = 0;
  _DAT_00e53cb0 = 0;
  _DAT_00e53cb4 = 0;
  _DAT_00e53cb8 = 0;
  _DAT_00e53cbc = 0;
  _DAT_00e53cc0 = 0;
  _DAT_00e53cc4 = 0;
  _DAT_00e53cc8 = 0;
  _DAT_00e53ccc = 0;
  _DAT_00e53cd0 = 0;
  _DAT_00e53cd4 = 0;
  _DAT_00e53cd8 = 0;
  _DAT_00e53cdc = 0;
  _DAT_00e53ce0 = 0;
  _DAT_00e53ce4 = 0;
  _DAT_00e53ce8 = 0;
  _DAT_00e53cec = 0;
  _DAT_00e53cf0 = 0;
  _DAT_00e53cf4 = 0;
  _DAT_00e53cf8 = 0;
  _DAT_00e53cfc = 0;
  _DAT_00e53d00 = 0;
  _DAT_00e53d04 = 0;
  _DAT_00e53d08 = 0;
  _DAT_00e53d0c = 0;
  _DAT_00e53d10 = 0;
  _DAT_00e53d14 = 0;
  _DAT_00e53d18 = 0;
  _DAT_00e53d1c = 0;
  _DAT_00e53d20 = 0;
  _DAT_00e53d24 = 0;
  _DAT_00e53d28 = 0;
  _DAT_00e53d2c = 0;
  _DAT_00e53d30 = 0;
  _DAT_00e53d34 = 0;
  _DAT_00e53d38 = 0;
  _DAT_00e53d3c = 0;
  _DAT_00e53d40 = 0;
  _DAT_00e53d44 = 0;
  _DAT_00e53d48 = 0;
  _DAT_00e53d4c = 0;

  return this;
}