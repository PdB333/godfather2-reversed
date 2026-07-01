// Xbox PDB: EARS_Modules_MultiplayerScenario_MultiplayerScenario
// FUNC_NAME: MultiplayerScenarioManager::constructor
undefined4 * __thiscall MultiplayerScenarioManager::constructor(undefined4 *this, undefined4 param_2)
{
  undefined4 uVar1;
  
  // Call base class constructors
  FUN_0046c590(param_2);
  FUN_004814b0();
  
  uVar1 = DAT_00d5c454;
  
  // Set vtable pointers
  this[0x14] = &PTR_LAB_00d7a0c8;  // +0x50 vtable entry
  *this = &PTR_FUN_00d79fc8;       // +0x00 vtable
  this[0xf] = &PTR_LAB_00d79fb8;   // +0x3C vtable entry
  this[0x12] = &PTR_LAB_00d79fb4;  // +0x48 vtable entry
  this[0x18] = 0;                   // +0x60 some pointer
  
  // Initialize scenario manager with 6 slots
  FUN_006a79f0(6, uVar1);
  
  uVar1 = DAT_00d5c454;
  
  // Initialize scenario state array (0x40 bytes each, 8 entries)
  this[0x1f] = 0x40;  // +0x7C scenario count or size
  this[0x20] = 0;      // +0x80
  this[0x21] = 0;      // +0x84
  this[0x22] = 0;      // +0x88
  this[0x23] = 0;      // +0x8C
  this[0x24] = 0;      // +0x90
  this[0x25] = 0;      // +0x94
  this[0x26] = 0;      // +0x98
  this[0x27] = 0;      // +0x9C
  this[0x28] = 0;      // +0xA0
  *(undefined2 *)(this + 0x29) = 0;  // +0xA4
  *(undefined2 *)((int)this + 0xa6) = 0;  // +0xA6
  this[0x2a] = 0;      // +0xA8
  *(undefined2 *)(this + 0x2b) = 0;  // +0xAC
  *(undefined2 *)((int)this + 0xae) = 0;  // +0xAE
  this[0x2c] = 0;      // +0xB0
  *(undefined2 *)(this + 0x2d) = 0;  // +0xB4
  *(undefined2 *)((int)this + 0xb6) = 0;  // +0xB6
  this[0x2e] = 0;      // +0xB8
  *(undefined2 *)(this + 0x2f) = 0;  // +0xBC
  *(undefined2 *)((int)this + 0xbe) = 0;  // +0xBE
  
  // Initialize scenario data
  FUN_008ab8d0(6, uVar1);
  
  // Initialize more state variables
  this[0x36] = 0;      // +0xD8
  this[0x37] = 0;      // +0xDC
  this[0x38] = 0;      // +0xE0
  this[0x39] = 0;      // +0xE4
  this[0x3a] = 0;      // +0xE8
  this[0x3b] = 0;      // +0xEC
  this[0x3c] = 0;      // +0xF0
  this[0x3d] = 0;      // +0xF4
  this[0x3e] = 0;      // +0xF8
  this[0x3f] = 0;      // +0xFC
  this[0x40] = 0;      // +0x100
  this[0x41] = 0;      // +0x104
  this[0x43] = 0;      // +0x10C
  this[0x45] = 0;      // +0x114
  this[0x46] = 0;      // +0x118
  this[0x47] = 0;      // +0x11C
  this[0x48] = 0;      // +0x120
  this[0x49] = 0;      // +0x124
  this[0x4a] = 0;      // +0x128
  this[0x4b] = 0;      // +0x12C
  this[0x4c] = 0;      // +0x130
  this[0x42] = 0xffffffff;  // +0x108 -1 (invalid)
  this[0x44] = 0xffffffff;  // +0x110 -1 (invalid)
  
  // Initialize score/state tracking
  this[0x50] = 0;      // +0x140
  this[0x4f] = 0;      // +0x13C
  this[0x4e] = 0;      // +0x138
  this[0x4d] = 0;      // +0x134
  
  // Initialize magic/sentinel values
  this[0x51] = 0xfe16702f;  // +0x144 magic
  this[0x52] = 0;            // +0x148
  this[0x53] = 0xbadbadba;   // +0x14C sentinel
  this[0x54] = 0xbeefbeef;   // +0x150 sentinel
  this[0x55] = 0xeac15a55;   // +0x154 sentinel
  this[0x56] = 0x91100911;   // +0x158 sentinel
  this[0x57] = 0;            // +0x15C
  this[0x58] = 0;            // +0x160
  this[0x59] = 0;            // +0x164
  this[0x5a] = 0;            // +0x168
  this[0x5b] = 0;            // +0x16C
  this[0x5c] = 0;            // +0x170
  this[0x5d] = 0;            // +0x174
  this[0x5e] = 0;            // +0x178
  this[0x5f] = 0;            // +0x17C
  this[0x60] = 0;            // +0x180
  
  // Register message handlers
  FUN_00408240(&DAT_0112ee84, "iMsgMultiplayerScenarioStarting");
  FUN_00408240(&DAT_0112ee7c, "iMsgMultiplayerScenarioCompleted");
  FUN_00408240(&DAT_0112f4b4, "iMsgMultiplayerRoundCompleted");
  FUN_00408240(&DAT_0112ecfc, "iMsgScoreBoardEventUpdate");
  FUN_00408240(&DAT_0112b534, "iMsgEnablePlayer");
  FUN_00408240(&DAT_0112b2a4, "iMsgDisablePlayer");
  FUN_00408240(&DAT_0112b214, "iMsgReviveAndTeleportPlayer");
  FUN_00408240(&DAT_0112f1dc, "iMsgSentientScoreboardRegistrationNotice");
  FUN_00408240(&DAT_0112f534, "Multiplayer Has gone into Overtime");
  FUN_00408240(&DAT_0112edf4, "iMsgVoipBroadcastStart");
  FUN_00408240(&DAT_0112ef7c, "iMsgVoipBroadcastStop");
  
  return this;
}