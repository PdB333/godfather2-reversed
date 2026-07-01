// FUNC_NAME: Player::registerNetFields
void __fastcall Player::registerNetFields(int this)
{
    // Call base class registration first
    FUN_005c1740();

    // Register network fields with their offsets, sizes, and flags
    // Each call: FUN_005c01d0(&DAT_xx, offset, size, 0, 0, 1)
    // The last parameter (1) likely indicates "isDirty" or "isReplicated"
    
    FUN_005c01d0(&DAT_00d88e80, this + 0x134, 6, 0, 0, 1);  // +0x134: some 6-byte field
    FUN_005c01d0(&DAT_00d85738, this + 0x124, 2, 0, 0, 1);  // +0x124: 2-byte field
    FUN_005c01d0(&DAT_00d88e78, this + 0x138, 6, 0, 0, 1);  // +0x138: 6-byte field
    FUN_005c01d0(&DAT_00d88e70, this + 0x13c, 6, 0, 0, 1);  // +0x13c: 6-byte field
    FUN_005c01d0(&DAT_00d88e68, this + 0x140, 6, 0, 0, 1);  // +0x140: 6-byte field
    FUN_005c01d0(&DAT_00d85720, this + 0x130, 6, 0, 0, 1);  // +0x130: 6-byte field
    FUN_005c01d0(&DAT_00d85718, this + 0x144, 1, 0, 0, 1);  // +0x144: 1-byte field
    FUN_005c01d0(&DAT_00d85730, this + 0x154, 1, 0, 0, 1);  // +0x154: 1-byte field
    FUN_005c01d0(&DAT_00d85710, this + 0x148, 6, 0, 0, 1);  // +0x148: 6-byte field
    FUN_005c01d0(&DAT_00d85708, this + 0x128, 1, 0, 0, 1);  // +0x128: 1-byte field
    FUN_005c01d0(&DAT_00d85700, this + 0x150, 1, 0, 0, 1);  // +0x150: 1-byte field
    FUN_005c01d0(&DAT_00e40ec8, this + 300, 6, 0, 0, 1);    // +0x12c: 6-byte field (300 = 0x12c)
    FUN_005c01d0(&DAT_00d88e60, this + 0x158, 6, 0, 0, 1);  // +0x158: 6-byte field
    FUN_005c01d0(&DAT_00d856f0, this + 0xe8, 1, 0, 0, 1);   // +0xe8: 1-byte field
    FUN_005c01d0(&DAT_00d856e0, this + 0x15c, 6, 0, 0, 1);  // +0x15c: 6-byte field
    FUN_005c01d0(&DAT_00d856d8, this + 0x160, 1, 0, 0, 1);  // +0x160: 1-byte field
    FUN_005c01d0(&DAT_00e3d6f8, this + 0x14c, 1, 0, 0, 1);  // +0x14c: 1-byte field
    FUN_005c01d0(&DAT_00d88e58, this + 0x164, 1, 0, 0, 1);  // +0x164: 1-byte field
    FUN_005c01d0(&DAT_00d88e50, this + 0x170, 2, 0, 0, 1);  // +0x170: 2-byte field
}