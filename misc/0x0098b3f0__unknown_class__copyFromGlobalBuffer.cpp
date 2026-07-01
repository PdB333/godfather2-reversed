// FUNC_NAME: unknown_class::copyFromGlobalBuffer
void __thiscall unknown_class::copyFromGlobalBuffer(void)
{
    FUN_005c1740(); // likely a reset or clear function
    if (DAT_01206978 != 0) {
        FUN_00408900(this + 0x4c, &DAT_01206978, 0x8000); // copy 32KB from global buffer to member at +0x4c
    }
}