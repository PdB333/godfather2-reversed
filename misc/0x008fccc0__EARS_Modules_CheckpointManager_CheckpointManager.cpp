// Xbox PDB: EARS_Modules_CheckpointManager_CheckpointManager
// FUNC_NAME: CheckpointManager::constructor
undefined4 * __fastcall CheckpointManager::constructor(undefined4 *this)
{
  // Vtable setup
  this[1] = &PTR_LAB_00d814f0; // +0x04: vtable for base class
  DAT_011299c4 = this; // Store singleton pointer
  this[2] = &PTR_FUN_00e2f19c; // +0x08: vtable for derived class
  this[3] = 1; // +0x0C: initialized flag
  this[4] = 0; // +0x10: current checkpoint index
  *this = &PTR_FUN_00d8159c; // +0x00: vtable pointer
  this[1] = &PTR_LAB_00d81598; // +0x04: vtable override
  this[2] = &PTR_LAB_00d81588; // +0x08: vtable override
  
  // Initialize checkpoint state
  this[5] = 0;  // +0x14: checkpoint count
  this[6] = 0;  // +0x18: active checkpoint
  this[7] = 0;  // +0x1C: checkpoint timer
  this[8] = 0;  // +0x20: checkpoint status
  this[9] = 0;  // +0x24: checkpoint data pointer
  this[10] = 0; // +0x28: checkpoint flags
  this[0xb] = 0; // +0x2C: checkpoint state
  this[0xc] = 0; // +0x30: checkpoint progress
  this[0xd] = 0; // +0x34: checkpoint restart data
  this[0xe] = 0; // +0x38: checkpoint trigger data
  this[0xf] = 0; // +0x3C: checkpoint debug data
  
  // Register message handlers
  FUN_00463980(0x4aba815, this, 7); // Register for checkpoint messages
  FUN_00408240(&DAT_0112fedc, "iMsgNewCheckpointLoaded");
  FUN_00408240(&DAT_0112fecc, "iMsgNewCheckpointStarted");
  FUN_00408240(&DAT_0112fec4, "iMsgNewCheckpointRestarted");
  FUN_00408240(&DAT_0112feb8, "iMsgCheckpointDebugRestarting");
  FUN_00408240(&DAT_0112fed4, "iMsgCheckpointFailed");
  
  return this;
}