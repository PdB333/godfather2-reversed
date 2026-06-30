// FUNC_NAME: SomeManager::dispatchUpdate

void __thiscall SomeManager::dispatchUpdate(
    uint param_unknown,                  // +0x00? passed as last arg to inner function
    uint param_a,
    uint param_b,
    uint param_c,
    uint param_d
)
{
    // Inner call: likely a virtual dispatch or generic handler
    // DAT_011f6a30 and DAT_011f6a70 are static function tables or config data
    FUN_00614440(param_a, param_b, param_c, param_d, &DAT_011f6a30, &DAT_011f6a70, param_unknown);

    // If a global debug flag (bit 0) is set, run additional processing
    if ((DAT_011f7430 & 1) != 0) {
        FUN_00614b90(); // possibly debug logging or post-update hook
    }
}