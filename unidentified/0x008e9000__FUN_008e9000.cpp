// FUNC_NAME: SomeEARSObject::~SomeEARSObject
void __fastcall SomeEARSObject::~SomeEARSObject(undefined4 *this)
{
  int iVar1;
  
  *this = &PTR_FUN_00d80b4c;
  this[0xf] = &PTR_LAB_00d80b3c;
  this[0x12] = &PTR_LAB_00d80b38;
  this[0x14] = &PTR_LAB_00d80b20;
  // Check flag at offset +0x8C (0x23 * 4) bit 1
  if (((uint)this[0x23] >> 1 & 1) != 0) {
    iVar1 = FUN_008e8e30();  // some resource check
    if (iVar1 != 0) {
      FUN_00791350(this + 0x14); // release resource at +0x50
    }
  }
  // Release four stream/sound resources at +0x64, +0x6C, +0x74, +0x7C
  FUN_004086d0(this + 0x19); // +0x64
  FUN_00408310(this + 0x19); // +0x64
  FUN_004086d0(this + 0x1b); // +0x6C
  FUN_00408310(this + 0x1b); // +0x6C
  FUN_004086d0(this + 0x1d); // +0x74
  FUN_00408310(this + 0x1d); // +0x74
  FUN_004086d0(this + 0x1f); // +0x7C
  FUN_00408310(this + 0x1f); // +0x7C
  FUN_00408310(this + 0x21); // +0x84
  FUN_008e6530(this);        // base class destructor or cleanup
  // Release three dynamically allocated objects at +0xA0, +0x98, +0x90
  if (this[0x28] != 0) {     // +0xA0
    FUN_004daf90(this + 0x28);
  }
  if (this[0x26] != 0) {     // +0x98
    FUN_004daf90(this + 0x26);
  }
  if (this[0x24] != 0) {     // +0x90
    FUN_004daf90(this + 0x24);
  }
  FUN_0046c640();            // global cleanup/shutdown
  return;
}