// FUNC_NAME: GameConfig::loadFromGlobals
void __fastcall GameConfig::loadFromGlobals(int this) {
    // Call base class initializer (likely sets some defaults)
    FUN_005c1740();

    // Bind local fields to global configuration values (type 0 or 2)
    // Parameters: globalAddr, localFieldAddr, type, unknown0, unknown1, flag
    FUN_005c01d0(&DAT_00d8c238, this + 0x6c, 0, 0, 0, 1); // +0x6c : some field
    FUN_005c01d0(&DAT_00d8c230, this + 0x74, 0, 0, 0, 1); // +0x74
    FUN_005c01d0(&DAT_00d8c228, this + 0x70, 0, 0, 0, 1); // +0x70
    FUN_005c01d0(&DAT_00d8c220, this + 0x50, 2, 0, 0, 1); // +0x50 (type=2)

    // Copy global constants into local fields
    *(int*)(this + 0x54) = DAT_01130034; // +0x54 : e.g., playerHpMax
    *(int*)(this + 0x64) = DAT_0113003c; // +0x64 : e.g., enemyDamage
    *(int*)(this + 0x68) = DAT_01130038; // +0x68 : e.g., playerArmor
    *(int*)(this + 0x5c) = DAT_0112e2e8; // +0x5c : e.g., reputationFactor
    *(int*)(this + 0x58) = DAT_0112fee4; // +0x58 : e.g., moneyMultiplier
    *(int*)(this + 0x60) = DAT_01130018; // +0x60 : e.g., missionTimer
}