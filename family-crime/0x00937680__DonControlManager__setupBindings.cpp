// FUNC_NAME: DonControlManager::setupBindings
// Address: 0x00937680
// Initializes controller input bindings for a control manager object.
// Associates global data tables with member fields for different button/axis types.
// The member fields at offsets +0x50, +0x54, +0x5C, +0x60, +0x64, +0x68
// appear to store pointers or handles to mapping entries.

void __thiscall DonControlManager::setupBindings(void)

{
  // Call base class or common initialization
  FUN_005c1740();

  // First two bindings (type 0: analog axes?)
  FUN_005c01d0(&DAT_00d8a1e4,this + 0x50,0,0,0,1);
  FUN_005c01d0(&DAT_00d8a1dc,this + 0x54,0,0,0,1);

  // Next four bindings (type 6: buttons?)
  FUN_005c01d0(&DAT_00d8a1d4,this + 0x5c,6,0,0,1);
  FUN_005c01d0(&DAT_00d8a1cc,this + 0x60,6,0,0,1);
  FUN_005c01d0(&DAT_00d8a1c4,this + 0x64,6,0,0,1);
  FUN_005c01d0(&DAT_00d8a1bc,this + 0x68,6,0,0,1);

  return;
}