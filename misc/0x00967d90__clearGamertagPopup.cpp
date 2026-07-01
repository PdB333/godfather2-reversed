// FUNC_NAME: clearGamertagPopup
void __fastcall clearGamertagPopup(uint32_t *playerIdPtr)
{
    // "ClearGamertagPopup" – likely a debug string or event name
    // FUN_005a04a0 is probably a logging or generic UI function
    // Arguments: text, some flag, some global data reference, another flag
    FUN_005a04a0("ClearGamertagPopup", 0, &DAT_00d8cdec, 0);

    // Store the player ID at offset 0xDC in the global game UI manager structure
    // DAT_01129930 points to a singleton (e.g., gGameUIManager)
    *(uint32_t *)(DAT_01129930 + 0xDC) = *playerIdPtr;
}