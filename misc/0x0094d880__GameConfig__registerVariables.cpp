// FUNC_NAME: GameConfig::registerVariables
void __fastcall GameConfig::registerVariables(int thisPtr)
{
    // Initialize config system base
    FUN_005c1740();

    // Register each gameplay variable with its name, pointer, type code (0=int/bool, 6=enum/float), and default flags (last param=1 likely means "save/loaded")
    FUN_005c01d0(&DAT_00d8b7cc, thisPtr + 0x54, 0, 0, 0, 1);   // +0x54: integer
    FUN_005c01d0(&DAT_00d8b7c8, thisPtr + 0x58, 6, 0, 0, 1);   // +0x58: enum/float
    FUN_005c01d0(&DAT_00d8b7c0, thisPtr + 0x5c, 0, 0, 0, 1);   // +0x5c: integer
    FUN_005c01d0(&DAT_00d8b7bc, thisPtr + 0x60, 6, 0, 0, 1);   // +0x60: enum/float
    FUN_005c01d0(&DAT_00d8b7b4, thisPtr + 100, 0, 0, 0, 1);    // +0x64: integer
    FUN_005c01d0(&DAT_00d8b7ac, thisPtr + 0x68, 6, 0, 0, 1);   // +0x68: enum/float
    FUN_005c01d0(&DAT_00d8b7a4, thisPtr + 0x74, 6, 0, 0, 1);   // +0x74: enum/float
    FUN_005c01d0(&DAT_00d8b79c, thisPtr + 0x78, 6, 0, 0, 1);   // +0x78: enum/float
    FUN_005c01d0(&DAT_00d8b794, thisPtr + 0x7c, 6, 0, 0, 1);   // +0x7c: enum/float
    FUN_005c01d0(&DAT_00d8b78c, thisPtr + 0x88, 4, 0, 0, 1);   // +0x88: type 4? (maybe float or double)
    FUN_005c01d0(&DAT_00d8b784, thisPtr + 0x8c, 4, 0, 0, 1);   // +0x8c: type 4
    FUN_005c01d0(&DAT_00d8b77c, thisPtr + 0x84, 0, 0, 0, 1);   // +0x84: integer
    FUN_005c01d0(&DAT_00d8b774, thisPtr + 0x70, 6, 0, 0, 1);   // +0x70: enum/float
    FUN_005c01d0(&DAT_00d8b76c, thisPtr + 0x90, 0, 0, 0, 1);   // +0x90: integer
}