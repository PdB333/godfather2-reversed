// FUNC_NAME: PlayerActionableInfo::initActionableSlots
void __fastcall PlayerActionableInfo::initActionableSlots(int this)
{
  FUN_005c1740();
  FUN_005c01d0(&DAT_00d8ca18, this + 0x68, 5, &LAB_0095a550, 0, 1);  // +0x68: slot array, 5 entries, with label callback
  FUN_005c01d0(&DAT_00d8ca10, this + 0x130, 6, 0, 0, 1);           // +0x130: slot array, 6 entries
  FUN_005c01d0(&DAT_00d8ca08, this + 0xec, 6, 0, 0, 1);            // +0xec: slot array, 6 entries
  FUN_005c01d0(&DAT_00d8ca00, this + 0xfc, 2, 0, 0, 1);            // +0xfc: slot array, 2 entries
  FUN_005c01d0(&DAT_00d8c9f8, this + 0x100, 6, 0, 0, 1);           // +0x100: slot array, 6 entries
  FUN_005c01d0(&DAT_00d8c9f0, this + 0x110, 6, 0, 0, 1);           // +0x110: slot array, 6 entries
  FUN_005c01d0(&DAT_00d8c9e8, this + 0x120, 6, 0, 0, 1);           // +0x120: slot array, 6 entries
  return;
}