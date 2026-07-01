// FUNC_NAME: InputManager::initControllerSlots
void __fastcall InputManager::initControllerSlots(int this)
{
  // Initialize controller slot data structures
  // Each call registers a callback or sets up a field at a specific offset
  // The offsets (0x1c, 0x20, 0x24, etc.) correspond to controller slot fields
  // +0x1c: some flag/state
  // +0x20: another flag/state
  // +0x24: yet another flag/state
  // +0x28: ...
  // +0x2c: ...
  // +0x34: ...
  // +0x38: ...
  // +0x3c: ...
  // +0x40: ...
  // +0x44: ...
  // +0x48: ...
  // +0x4c: ...
  // +0x54: ...
  // +0x58: ...
  // +0x5c: ...
  // +0x60: ...
  // +0x64: ...
  // +0x68: ...
  // +0x6c: ...

  // Register callback for slot field at +0x1c
  FUN_005c0400(&DAT_00d92130, this + 0x1c, &LAB_00992b30, 0, 0);
  // Register callback for slot field at +0x20
  FUN_005c03d0(&DAT_00d8ca78, this + 0x20, 0, 0, 1);
  // Register callback for slot field at +0x24
  FUN_005c0430(&DAT_00d8be3c, this + 0x24, 0, 0, 1, 1);
  // Register callback for slot field at +0x28
  FUN_005c0430(&DAT_00d8be34, this + 0x28, 0, 0, 1, 1);
  // Register callback for slot field at +0x2c
  FUN_005c0430(&DAT_00d92128, this + 0x2c, 0, 0, 1, 1);
  // Register callback for slot field at +0x34
  FUN_005c0400(&DAT_00d92120, this + 0x34, 0, 0, 1);
  // Register callback for slot field at +0x38
  FUN_005c0400(&DAT_00d92118, this + 0x38, 0, 0, 1);
  // Register callback for slot field at +0x3c
  FUN_005c0400(&DAT_00d92110, this + 0x3c, 0, 0, 1);
  // Register callback for slot field at +0x40
  FUN_005c0400(&DAT_00d92108, this + 0x40, 0, 0, 1);
  // Register callback for slot field at +0x44
  FUN_005c04b0(&DAT_00d92100, this + 0x44, 0, 0, 1);
  // Register callback for slot field at +0x48
  FUN_005c04b0(&DAT_00d920f8, this + 0x48, 0, 0, 1);
  // Register callback for slot field at +0x4c
  FUN_005c0430(&DAT_00d920f0, this + 0x4c, 0, 0, 1, 1);
  // Register callback for slot field at +0x54
  FUN_005c0400(&DAT_00d920e8, this + 0x54, 0, 0, 1);
  // Register callback for slot field at +0x58
  FUN_005c0400(&DAT_00d920e0, this + 0x58, 0, 0, 1);
  // Register callback for slot field at +0x5c
  FUN_005c0400(&DAT_00d920d8, this + 0x5c, 0, 0, 1);
  // Register callback for slot field at +0x60
  FUN_005c0400(&DAT_00d920d0, this + 0x60, 0, 0, 1);
  // Register callback for slot field at +0x64
  FUN_005c04b0(&DAT_00d920c8, this + 100, 0, 0, 1);
  // Register callback for slot field at +0x68
  FUN_005c0430(&DAT_00d920c0, this + 0x68, 0, 0, 1, 1);
  // Register callback for slot field at +0x6c
  FUN_005c04e0(&DAT_00d920b8, this + 0x6c, 0, 0, 1);
  // Finalize initialization
  FUN_005c0890();
}