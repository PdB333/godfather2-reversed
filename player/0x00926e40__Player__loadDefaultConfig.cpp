// FUNC_NAME: Player::loadDefaultConfig
void __thiscall Player::loadDefaultConfig(void)
{
    FUN_005c1740(); // base class initialization
    FUN_005c01d0(&DAT_00d83fd4, this + 0x3a4, 4, 0, 0, 1); // copy int field at +0x3a4
    FUN_005c01d0(&DAT_00d83fd0, this + 0x3a8, 4, 0, 0, 1); // copy int field at +0x3a8
    FUN_005c01d0(&DAT_00d879f0, this + 0x3c4, 2, 0, 0, 1); // copy short field at +0x3c4
    FUN_005c01d0(&DAT_00d879ec, this + 0x3c5, 2, 0, 0, 1); // copy short field at +0x3c5 (overlaps with previous)
    FUN_005c01d0(&DAT_00e3deb4, this + 0x3c6, 2, 0, 0, 1); // copy short field at +0x3c6
    // Set bool at +0x3a0 based on global game mode indicator
    *(bool *)(this + 0x3a0) = *(char *)(DAT_012233b4 + 0x564) != 18;
}