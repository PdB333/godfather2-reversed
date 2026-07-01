// Xbox PDB: EARS_Apt_UIHud_HideBankHeistInfo
// FUNC_NAME: hideBankHeistInfo
void hideBankHeistInfo(void)
{
    // Call generic command dispatcher to hide bank heist UI
    // FUN_005a04a0 is likely a UI command handler (e.g., UIManager::executeCommand)
    FUN_005a04a0("HideBankHeistInfo", 0, &DAT_00d8a64c, 0);
    return;
}