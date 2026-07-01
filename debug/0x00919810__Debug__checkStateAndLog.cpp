// FUNC_NAME: Debug::checkStateAndLog
void __fastcall Debug::checkStateAndLog(int this)
{
    // Check if the state value at offset +0xB8 is in range [10, 25]
    if ((*(unsigned int *)(this + 0xB8) - 10U) < 0x10) {
        // Log debug message (format string at DAT_01130448)
        FUN_00402050((int)&DAT_01130448, 0);
        // Perform additional state reset or update
        FUN_00918170();
    }
    return;
}