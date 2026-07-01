// FUNC_NAME: Player::initializeFromGlobalConfig
void __fastcall Player::initializeFromGlobalConfig(Player* this) {
    // Call some global initialization (maybe input or renderer)
    FUN_004c3920();

    // Fetch global configuration object pointer
    int* globalConfig = DAT_01129938;

    // Copy values from global config into this instance
    // Offsets based on observed patterns: +0x34, +0x3C, +0x14 (bit3)
    *(int*)(this + 0x70) = *(int*)(globalConfig + 0x34);  // e.g., some float or int field
    *(int*)(this + 0x74) = *(int*)(globalConfig + 0x3C);
    // Bit3 of globalConfig+0x14 extracted and stored as uint at this+0x78
    *(uint*)(this + 0x78) = (*(uint*)(globalConfig + 0x14) >> 3) & 1;

    // Call further initialization using a pointer stored at this+0x58
    FUN_009243b0(*(int*)(this + 0x58));  // maybe a sound or animation resource

    // Additional setup calls
    FUN_00924360();
    FUN_00923590();
}