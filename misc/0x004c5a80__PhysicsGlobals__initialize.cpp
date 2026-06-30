// FUNC_NAME: PhysicsGlobals::initialize
undefined * PhysicsGlobals::initialize(void)

{
  FUN_006126d0();
  // +0xbc global variables for physics engine
  _DAT_012181cc = DAT_00e2b1a4;  // gravity magnitude
  _DAT_012181d0 = DAT_00e2b1a4;  // air resistance multiplier
  _DAT_012181d4 = DAT_00e2e230;  // friction coefficient
  _DAT_01218110 = &PTR_LAB_00e36364;  // vtable pointer
  _DAT_012181d8 = 0;  // +0x58 flags: collision enabled
  _DAT_012181dc = 0;  // +0x5c flags: gravity enabled
  _DAT_012181e0 = 0;  // +0x60 flags: air resistance enabled
  _DAT_012181e4 = 0;  // +0x64 flags: friction enabled
  _DAT_012181e8 = 0;  // +0x68 flags: simulation paused
  _DAT_012181b4 = 0;  // +0x34 simulation time step
  return &DAT_01218110;  // return pointer to physics globals structure
}