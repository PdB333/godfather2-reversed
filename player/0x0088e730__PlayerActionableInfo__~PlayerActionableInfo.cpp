// FUNC_NAME: PlayerActionableInfo::~PlayerActionableInfo
void __fastcall PlayerActionableInfo::~PlayerActionableInfo(undefined4 *this)

{
  undefined4 *puVar1;
  
  *this = &PTR_FUN_00d771a0;
  this[0xf] = &PTR_LAB_00d77190;
  this[0x12] = &PTR_LAB_00d7718c;
  if (this[0x1a] != 0) {
    // Free audio resource at offset 0x68
    FUN_009c8f10(this[0x1a]);
  }
  // Free 4 string buffers at offsets 0x50, 0x58, 0x60, 0x68
  FUN_004086d0(this + 0x14);
  FUN_00408310(this + 0x14);
  FUN_00408310(this + 0x16);
  FUN_00408310(this + 0x18);
  // Deallocate global string pools
  FUN_004086d0(&DAT_012069c4);
  FUN_004086d0(&DAT_0120685c);
  FUN_004086d0(&DAT_01130390);
  FUN_004086d0(&DAT_01130218);
  puVar1 = (undefined4 *)FUN_0088d540(*(undefined1 *)(this + 0x21)); // +0x84: some ID
  if (puVar1 == this) {
    FUN_0088d4f0(0,*(undefined1 *)(this + 0x21)); // Remove from global list
  }
  FUN_0046c640(); // Decrement reference / cleanup
  return;
}