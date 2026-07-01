// FUNC_NAME: PopupManager::closePopup
void PopupManager::closePopup(void)
{
    // +0x310: some state flag or pointer (DAT_01130310)
    // FUN_00402050 likely sets a flag or clears state
    FUN_00402050(&DAT_01130310, 0);
    
    // +0xd34: string constant "ClosePopup" (DAT_00d90d34)
    // FUN_005a04a0 likely dispatches a UI event or callback
    FUN_005a04a0("ClosePopup", 0, &DAT_00d90d34, 0);
}