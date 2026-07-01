// FUNC_NAME: Player::resetCombatState
undefined4 __fastcall Player::resetCombatState(int this)
{
    undefined4 local_c;
    undefined4 local_8;
    undefined1 local_4;

    // Clear combat timer or flag at offset 0x14c
    *(undefined4 *)(this + 0x14c) = 0;

    // Initialize a local struct (possibly a timer or event) with global constant and zeros
    local_c = DAT_01130408;  // Global constant (e.g., combat cooldown duration)
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c, 0);  // Likely a function to set up a timer or clear a buffer

    return 1;  // Success
}