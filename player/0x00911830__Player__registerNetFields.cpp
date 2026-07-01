// FUNC_NAME: Player::registerNetFields
void __fastcall Player::registerNetFields(int this)
{
    // Call base class net field registration
    FUN_005c1740();
    
    // Register net fields with various types and flags
    // +0x2e8: 1 byte field
    FUN_005c01d0(&DAT_00d83fc8, this + 0x2e8, 1, 0, 0, 0);
    // +0x260: 5 byte field
    FUN_005c01d0(&DAT_00d83fc0, this + 0x260, 5, 0, 0, 0);
    // +0x2e4: 1 byte field
    FUN_005c01d0(&DAT_00d83fb8, this + 0x2e4, 1, 0, 0, 0);
    // +0x50: 5 byte field with flag 1
    FUN_005c01d0(&DAT_00d83fb0, this + 0x50, 5, 0, 0, 1);
    // +0xd4: 5 byte field with flag 1
    FUN_005c01d0(&DAT_00d83fa8, this + 0xd4, 5, 0, 0, 1);
    // +0x158: 5 byte field with flag 1
    FUN_005c01d0(&DAT_00d83fa0, this + 0x158, 5, 0, 0, 1);
    // +0x1dc: 5 byte field with callback at 0x009117f0
    FUN_005c01d0(&DAT_00d83f98, this + 0x1dc, 5, &LAB_009117f0, 0, 0);
    // +0x2ec: 2 byte field with callback at 0x00911800
    FUN_005c01d0(&DAT_00d83f90, this + 0x2ec, 2, &LAB_00911800, 0, 0);
    // +0x2ed: 2 byte field
    FUN_005c01d0(&DAT_00e41eb8, this + 0x2ed, 2, 0, 0, 0);
    // +0x2f0: 1 byte field with callback at 0x009101d0
    FUN_005c01d0(&DAT_00d83f88, this + 0x2f0, 1, &LAB_009101d0, 0, 0);
}