// Xbox PDB: EARS_Modules_InGameVideoPlayer_InGameVideoPlayer
// FUNC_NAME: VideoPlayer::VideoPlayer
undefined4 * __thiscall VideoPlayer::VideoPlayer(undefined4 *this, undefined4 param_2) {
  undefined4 *vtablePtr;

  // Call base class constructor (likely some Object or MediaBase)
  FUN_0046c590(param_2);

  // Setup vtable
  *this = &PTR_FUN_00d750a0; // Primary vtable

  // Setup sub-vtables for interfaces
  this[0xf] = &PTR_LAB_00d75090;  // +0x3C: vtable for video player interface
  this[0x12] = &PTR_LAB_00d7508c; // +0x48: vtable for another interface

  // Initialize members
  this[0x14] = 0; // +0x50
  *(undefined2 *)(this + 0x15) = 0; // +0x54 (low word)
  *(undefined2 *)((int)this + 0x56) = 0; // +0x56 (high word)
  this[0x16] = 0; // +0x58
  *(undefined2 *)(this + 0x17) = 0; // +0x5C (low)
  *(undefined2 *)((int)this + 0x5e) = 0; // +0x5E (high)
  this[0x18] = 0; // +0x60
  this[0x19] = 0; // +0x64
  this[0x1a] = 0; // +0x68
  this[0x1b] = 0; // +0x6C
  this[0x1c] = 0; // +0x70
  this[0x1d] = 0; // +0x74
  this[0x1e] = 0; // +0x78
  this[0x1f] = 0; // +0x7C

  vtablePtr = this + 0xf; // Points to the sub-vtable area

  this[0x20] = 0; // +0x80
  this[0x21] = 0; // +0x84
  this[0x22] = 0; // +0x88
  this[0x23] = 0; // +0x8C
  this[0x24] = 0; // +0x90
  this[0x25] = 0; // +0x94
  this[0x26] = 0; // +0x98
  this[0x27] = 0; // +0x9C
  this[0x28] = 0; // +0xA0
  this[0x29] = 0; // +0xA4
  this[0x2a] = 0; // +0xA8

  this[0x24] = this[0x24] | 0xc; // +0x90: set bits 0x0C (flags)

  // Register for video player shutdown notification if string is loaded
  if (DAT_01129a7c != 0) {
    FUN_00408900(vtablePtr, &DAT_01129a7c, 0x8000);
  }

  // Register message types with the messaging system
  FUN_00408240(&DAT_0112ddd8, "iMsgSystemRequestVideoPlayerShutdown");
  FUN_00408240(&DAT_0112dde0, "iMsgSystemVideoPlayerShutdownPending");
  FUN_00408240(&DAT_0112dde8, "iMsgSystemVideoPlayerShutdownComplete");
  FUN_00408240(&DAT_0112ddc4, "iMsgAudPauseAtmosScript");
  FUN_00408240(&DAT_0112ddd0, "iMsgAudUnPauseAtmosScript");
  FUN_00408240(&DAT_01218020, "iMsgMovieEnded");
  FUN_00408240(&DAT_01218028, "iMsgMoviePlayerEnded");
  FUN_00408240(&DAT_0112ddf8, "iMsgPauseInGameVideo");
  FUN_00408240(&DAT_0112ddf0, "iMsgUnpauseInGameVideo");

  // Register for additional notifications
  if (DAT_01129aa0 != 0) {
    FUN_00408900(vtablePtr, &DAT_01129aa0, 0x8000);
  }

  if (DAT_0112ddf8 != 0) {
    FUN_00408900(vtablePtr, &DAT_0112ddf8, 0x8000);
  }

  return this;
}