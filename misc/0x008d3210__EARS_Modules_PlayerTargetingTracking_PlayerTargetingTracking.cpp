// Xbox PDB: EARS_Modules_PlayerTargetingTracking_PlayerTargetingTracking
// FUNC_NAME: TargetingManager::constructor
undefined4 * __fastcall TargetingManager::constructor(undefined4 *this)
{
  int iVar1;
  
  this[1] = 1; // +0x04: some flag, initialized to 1
  this[2] = 0; // +0x08: counter or state, initialized to 0
  this[3] = &PTR_LAB_00d7d480; // +0x0C: vtable or interface pointer
  DAT_011299a4 = this; // global singleton pointer to TargetingManager
  *this = &PTR_FUN_00d7d4a4; // +0x00: vtable pointer
  this[3] = &PTR_LAB_00d7d4a0; // +0x0C: override vtable/interface
  this[4] = 0; // +0x10: some pointer or handle, null
  this[6] = 0; // +0x18: some pointer or handle, null
  this[7] = 0; // +0x1C: some pointer or handle, null
  this[8] = 0; // +0x20: some pointer or handle, null
  iVar1 = 4;
  do {
    FUN_008d5e80(); // likely initializes some sub-system or allocates memory
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  FUN_008d5e80(); // one more call
  this[5] = DAT_00d5ef50; // +0x14: copy some global value
  if (DAT_012069d4 != 0) {
    FUN_00408900(this, &DAT_012069d4, 0x8000); // register message handler with size 0x8000
  }
  FUN_00408240(&DAT_0112f9d0, "iMsgPlayerTargetingComputed"); // register message name
  if (DAT_0112b36c != 0) {
    FUN_00408900(this, &DAT_0112b36c, 0x8000); // register another message handler
  }
  return this;
}