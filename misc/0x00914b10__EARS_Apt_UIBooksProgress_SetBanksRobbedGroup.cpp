// Xbox PDB: EARS_Apt_UIBooksProgress_SetBanksRobbedGroup
// FUNC_NAME: BankProgressMenu::populateBanks
// Address: 0x00914b10
// Role: Populates the progress menu with bank robbery entries, checking discovery and distance.

void __fastcall BankProgressMenu::populateBanks(int thisPtr)
{
    bool bIsKnown;
    char cIsDiscovered;
    int iBankData;
    undefined4 *pBankEntry;
    char *pcBankName;
    undefined4 *pNextEntry;
    char *pcStatusString;
    float fDistance;
    int iLoopCount;

    // Initialize progress group for banks robbed
    FUN_005a04a0("ProgressSetGroup", 0, &DAT_00d84448, 1, "$dv_menu_books_progress_banks_robbed");
    *(int *)(thisPtr + 4) = 0; // Reset counter at offset +4

    iLoopCount = 20; // 0x14
    pBankEntry = DAT_0112a554; // Global array of bank entries (size unknown, step 0xC)

    do {
        pNextEntry = pBankEntry + 0xc; // Move to next entry? (offset 12 bytes)
        // Check if entry is valid: pNextEntry not equal to sentinel 0x20 and flag at offset 0x34 (pBankEntry[0xd]) is zero
        if ((pNextEntry != (undefined4 *)0x20) && (pBankEntry[0xd] == 0)) {
            iBankData = FUN_006b0ee0(*pNextEntry); // Get bank data from first field of next entry
            if (iBankData != 0) {
                cIsDiscovered = FUN_006b4440(); // Check if bank is discovered (global state?)
                if (cIsDiscovered == '\0') {
                    bIsKnown = false;
                } else {
                    cIsDiscovered = FUN_00849ea0(*(undefined4 *)(iBankData + 0x48)); // Check specific flag at offset 0x48
                    if (cIsDiscovered == '\0') {
                        bIsKnown = false;
                    } else {
                        bIsKnown = true;
                    }
                }
                fDistance = 0.0;
                FUN_008934e0(pBankEntry[0xf], &fDistance); // Get distance from field at offset 0x3C (pBankEntry[0xf])
                if (fDistance <= _DAT_00d577a0) { // Within threshold
                    if (bIsKnown) {
                        pBankEntry = (undefined4 *)FUN_006b2160(); // Get localized bank name
                        pcBankName = (char *)*pBankEntry;
                        if (pcBankName == (char *)0x0) {
                            pcBankName = &DAT_0120546e; // Default name
                        }
                        pcStatusString = "Bank";
                    } else {
                        pcBankName = "$dv_mono_unknown_loc";
                        pcStatusString = "Unknown";
                    }
                } else {
                    pBankEntry = (undefined4 *)FUN_006b2160(); // Get localized bank name
                    pcBankName = (char *)*pBankEntry;
                    if (pcBankName == (char *)0x0) {
                        pcBankName = &DAT_0120546e;
                    }
                    pcStatusString = "BankChecked"; // Already visited/checked
                }
                // Add item to progress menu
                FUN_005a04a0("ProgressAddItem", 0, &DAT_00d84448, 3, &DAT_00e36d94, pcStatusString, pcBankName);
                *(int *)(thisPtr + 4) = *(int *)(thisPtr + 4) + 1; // Increment counter
            }
        }
        iLoopCount = iLoopCount - 1;
        pBankEntry = pNextEntry;
        if (iLoopCount == 0) {
            return;
        }
    } while (true);
}