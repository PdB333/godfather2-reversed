// Xbox PDB: EARS_Modules_FamilyManager_FamilyManager
// FUNC_NAME: StrategyGameManager::constructor
undefined4 * __fastcall StrategyGameManager::constructor(undefined4 *this)
{
  this[1] = &PTR_LAB_00d7bdf8;
  DAT_01129904 = this;
  this[2] = &PTR_FUN_00e2f19c;
  this[4] = 0;
  this[3] = 1;
  *this = &PTR_FUN_00d7be58;
  this[1] = &PTR_LAB_00d7be54;
  this[2] = &PTR_LAB_00d7be44;
  this[9] = 0;   // +0x24
  this[10] = 0;  // +0x28
  this[0xb] = 0; // +0x2C
  this[0xc] = 0; // +0x30
  this[0xd] = 0; // +0x34
  this[0xe] = 0; // +0x38
  *(undefined1 *)(this + 0xf) = 0;  // +0x3C
  *(undefined1 *)((int)this + 0x3d) = 1; // +0x3D
  FUN_00463980(0xb604dd4, this, 3); // some initialization call with constant ID
  this[5] = 0xffffffff;  // +0x14
  this[6] = 0xffffffff;  // +0x18
  this[7] = 0xffffffff;  // +0x1C
  this[8] = 0xffffffff;  // +0x20
  FUN_00408240(&DAT_0112f960, "iMsgPauseStrategyGame"); // register message
  FUN_00408240(&DAT_0112f94c, "iMsgUnPauseStrategyGame"); // register message
  FUN_00408240(&DAT_0112f958, "iMsgPlayerVenueBombed"); // register message
  if (DAT_01206a20 != 0) {
    FUN_00408900(this + 2, &DAT_01206a20, 0x8000); // attach event listener
  }
  return this;
}