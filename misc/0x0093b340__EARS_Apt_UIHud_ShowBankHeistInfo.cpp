// Xbox PDB: EARS_Apt_UIHud_ShowBankHeistInfo
// FUNC_NAME: GodfatherGameManager::showBankHeistInfo
void GodfatherGameManager::showBankHeistInfo(int param_1)
{
    char* strPtr = nullptr;
    int local_c = 0;
    int local_8 = 0;
    void (*deallocFunc)(void*) = nullptr;

    FUN_00604000(param_1, &strPtr, 1); // Get localized string or data
    char* displayStr = strPtr;
    if (strPtr == nullptr) {
        displayStr = &DAT_0120546e; // Default fallback string
    }
    FUN_005a04a0("ShowBankHeistInfo", 0, &DAT_00d8a64c, 1, displayStr); // Show UI notification
    if (strPtr != nullptr) {
        deallocFunc(strPtr); // Free allocated string
    }
}