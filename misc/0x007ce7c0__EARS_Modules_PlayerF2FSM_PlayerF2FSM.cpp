// Xbox PDB: EARS_Modules_PlayerF2FSM_PlayerF2FSM
// FUNC_NAME: PlayerF2FSM::PlayerF2FSM

undefined4 * __thiscall PlayerF2FSM::PlayerF2FSM(undefined4 *this, undefined4 param1, undefined4 param2)
{
  int *field_0x1b4; // param_1 + 0x6d (0x6d*4 = 0x1B4)

  // Base class constructor calls
  FUN_007ab5e0(param1, param2);  // BaseAudioManager::BaseAudioManager
  FUN_007ca800();                // Some initialization (maybe audio system)

  // Set vtable pointers (multiple inheritance)
  this[0x26] = &PTR_FUN_00e32808;          // +0x98 - temporary vtable
  this[0x27] = 0;                           // +0x9C
  *this = &PTR_LAB_00d6eba8;               // +0x00 - primary vtable
  this[0x1d] = &PTR_LAB_00d6eba4;          // +0x74 - secondary vtable
  this[0x26] = &PTR_LAB_00d6eba0;          // +0x98 - final vtable (overwrites)

  FUN_0081a870();  // Some post-vtable setup

  // Initialize F2F state fields
  this[0x6c] = 0;   // +0x1B0
  this[0x6d] = 0;   // +0x1B4 (field_0x1b4)
  this[0x6e] = 0;   // +0x1B8
  this[0x74] = 0;   // +0x1D0
  this[0x7b] = 0;   // +0x1EC
  this[0x7c] = 0;   // +0x1F0
  this[0x7d] = 0;   // +0x1F4
  this[0x7e] = 0;   // +0x1F8
  this[0x7f] = 0;   // +0x1FC
  this[0x80] = 0;   // +0x200
  this[0x81] = 0;   // +0x204
  this[0x82] = 0;   // +0x208
  this[0x6a] = 0;   // +0x1A8
  this[0x68] = 0;   // +0x1A0
  this[0x6f] = 0;   // +0x1BC
  this[0x70] = 0;   // +0x1C0
  this[0x72] = 0;   // +0x1C8
  this[0x6b] = 0;   // +0x1AC

  // Possibly free a pointer
  field_0x1b4 = (int *)(this + 0x6d);
  if (*field_0x1b4 != 0) {
    FUN_004daf90(field_0x1b4);  // free or release
    *field_0x1b4 = 0;
  }

  this[0x71] = _DAT_00d5780c;  // +0x1C4 - global audio timestamp/ID
  this[0x74] = this[0x74] & 0xfffff3e1;  // +0x1D0 - clear some flags

  // Set boolean flags
  *(undefined2 *)(this + 0x75) = 0;        // +0x1D4 - 16-bit zero
  this[0x79] = 0;                           // +0x1E4
  this[0x7a] = 0;                           // +0x1E8
  *(undefined2 *)(this + 0x76) = 1;         // +0x1D8 - 16-bit true
  *(undefined2 *)((int)this + 0x1d6) = 0;   // +0x1D6 - 16-bit zero

  this[0x73] = 0;                           // +0x1CC

  FUN_006f8370();  // Additional audio/conversation setup

  // Register F2F audio message names
  FUN_00408240(&DAT_0112ba94, "iMsgAudioF2FInitiated");
  FUN_00408240(&DAT_0112ba84, "iMsgAudioF2FInitiatedBribeLite");
  FUN_00408240(&DAT_0112ba60, "iMsgAudioF2FInitiatedPoliceOfficer");
  FUN_00408240(&DAT_0112ba7c, "iMsgAudioF2FInitiatedMerchant");
  FUN_00408240(&DAT_0112ba68, "iMsgAudioF2FInitiatedRacket");
  FUN_00408240(&DAT_0112ba8c, "iMsgAudioF2FInitiatedInterrogation");
  FUN_00408240(&DAT_0112ba74, "iMsgAudioF2FInitiatedSpeciaCase");

  // Last byte flags
  *(undefined1 *)((int)this + 0x20d) = 0;  // +0x20D
  *(undefined1 *)((int)this + 0x20e) = 0;  // +0x20E

  return this;
}