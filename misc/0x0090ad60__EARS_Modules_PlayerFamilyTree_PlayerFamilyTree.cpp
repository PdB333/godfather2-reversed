// Xbox PDB: EARS_Modules_PlayerFamilyTree_PlayerFamilyTree
// FUNC_NAME: NetConnection::initMessageTypes
undefined4 * __fastcall NetConnection::initMessageTypes(undefined4 *this)
{
  int iVar1;
  
  this[1] = 1;
  this[2] = 0;
  this[3] = &PTR_LAB_00d832e8;  // vtable for NetConnection
  DAT_0112989c = this;  // global singleton pointer
  this[4] = &PTR_LAB_00d5e214;  // vtable for some base class
  *this = &PTR_FUN_00d833a8;  // vtable pointer
  this[3] = &PTR_LAB_00d833a4;  // update vtable entry
  this[4] = &PTR_LAB_00d8338c;  // update vtable entry
  this[5] = 0;  // some flag
  iVar1 = 6;
  do {
    FUN_0090a460();  // likely allocate or initialize message type
    iVar1 = iVar1 + -1;
  } while (-1 < iVar1);
  FUN_00408240(&DAT_0112ff88,"iMsgTreeType1S");  // register message type
  FUN_00408240(&DAT_0112ffb4,"iMsgTreeType2S");
  FUN_00408240(&DAT_0112ffbc,"iMsgTreeType3S");
  FUN_00408240(&DAT_0112ffa4,"iMsgTreeType1C3S");
  FUN_00408240(&DAT_0112ffc4,"iMsgTreeType1C4S");
  FUN_00408240(&DAT_0112ffac,"iMsgTreeType1Con1C4S");
  FUN_00408240(&DAT_0112ff94,"iMsgTreeType1Con2C4S");
  FUN_00408240(&DAT_0112ff9c,"iMsgTreeType1Con1U2C4S");
  if (DAT_0112ff88 != 0) {
    FUN_00408900(this,&DAT_0112ff88,0x8000);  // register message type with size 0x8000
  }
  if (DAT_0112ffb4 != 0) {
    FUN_00408900(this,&DAT_0112ffb4,0x8000);
  }
  if (DAT_0112ffbc != 0) {
    FUN_00408900(this,&DAT_0112ffbc,0x8000);
  }
  if (DAT_0112ffa4 != 0) {
    FUN_00408900(this,&DAT_0112ffa4,0x8000);
  }
  if (DAT_0112ffc4 != 0) {
    FUN_00408900(this,&DAT_0112ffc4,0x8000);
  }
  if (DAT_0112ffac != 0) {
    FUN_00408900(this,&DAT_0112ffac,0x8000);
  }
  if (DAT_0112ff94 != 0) {
    FUN_00408900(this,&DAT_0112ff94,0x8000);
  }
  if (DAT_0112ff9c != 0) {
    FUN_00408900(this,&DAT_0112ff9c,0x8000);
  }
  this[7] = 3;   // +0x1C: some message type count or index
  this[0x10] = 3;  // +0x40
  this[0x19] = 3;  // +0x64
  this[0x22] = 3;  // +0x88
  this[0x2b] = 4;  // +0xAC
  this[0x34] = 4;  // +0xD0
  this[0x3d] = 5;  // +0xF4
  return this;
}