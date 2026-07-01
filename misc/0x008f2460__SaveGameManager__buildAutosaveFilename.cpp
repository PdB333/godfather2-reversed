// FUNC_NAME: SaveGameManager::buildAutosaveFilename
void __fastcall SaveGameManager::buildAutosaveFilename(int this)
{
    undefined4 uVar1;
    char *_Source;
    char *local_10;
    undefined4 local_c;
    undefined4 local_8;
    code *local_4;
    
    local_10 = (char *)0x0;
    local_c = 0;
    local_8 = 0;
    local_4 = (code *)0x0;
    uVar1 = FUN_00602e60(0xffffffff); // Get current platform ID or language
    FUN_004d4ad0(&local_10,"GF2-%s-",uVar1); // Format: "GF2-<platform>-"
    FUN_004d55a0(); // Possibly string cleanup or memory management
    FUN_004d4300("autosave"); // Append "autosave" to the string
    _Source = local_10;
    if (local_10 == (char *)0x0) {
        _Source = &DAT_0120546e; // Empty string fallback
    }
    _strncpy((char *)(this + 0x2050),_Source,0x3f); // Copy to save filename buffer at +0x2050, max 63 chars
    *(undefined1 *)(this + 0x208f) = 0; // Null-terminate at +0x208f
    if (local_10 != (char *)0x0) {
        (*local_4)(local_10); // Free allocated string
    }
    return;
}