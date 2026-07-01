// FUNC_NAME: ActionOptions::initActionVariables
void __thiscall ActionOptions::initActionVariables(void* this) {
    // Unknown global initialization (possibly EARS system init)
    FUN_005c1740();

    // Register a 1-byte variable at offset 0x6c (no callback)
    FUN_005c01d0(&DAT_00d897b4, (int)this + 0x6c, 1, 0, 0, 0);

    // Register a 2-byte variable at offset 0x70 with callback at 0x00931a20
    FUN_005c01d0(&DAT_00d897ac, (int)this + 0x70, 2, 0, &LAB_00931a20, 0);

    // Register a 2-byte variable at offset 0x71 (no callback)
    FUN_005c01d0(&DAT_00d897a4, (int)this + 0x71, 2, 0, 0, 0);
}