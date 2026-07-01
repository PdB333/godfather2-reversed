// Xbox PDB: EARS_Apt_UIAccomplishment_ShowRivalFamilyEliminatedInfo
// FUNC_NAME: FamilyManager::handleFamilyElimination

void __fastcall FamilyManager::handleFamilyElimination(void *thisPtr) {
    char *familyName;
    int familyData;
    char *str1;
    char *str2;
    char *unusedString;
    char *local_30;
    char *local_20;
    // Stack strings (likely std::string or custom string objects with destructor pointers)
    // For clarity we treat them as raw char* with manual deallocation.

    // Call Flash: gotoAndPlay on the main Flash interface (DAT_00d83810)
    FlashMethodCall("gotoAndPlay", 0, gFlashInterface, 1, "rival_family");

    // Get family data from this object at offset 0x80
    familyData = getFamilyData(*(int *)((char *)thisPtr + 0x80));
    if (familyData != 0) {
        char *familyNamePtr;

        // Initialize stack strings (destructors stored as function pointers, here we allocate and format)
        // In reality these are objects; we simulate with char* and manual free later.
        // local_20 and local_30 will hold formatted strings.
        char *tempName;

        // Get the current family name (global)
        familyNamePtr = *(char **)getCurrentFamilyNamePtr(); // Returns pointer to global family name string
        if (familyNamePtr == nullptr) {
            familyNamePtr = kEmptyString;  // DAT_0120546e
        }

        // Build first message: "{f:%s}{$fanfare_family_eliminated_01}"
        stringFormat(&local_20, "{f:%s}{$fanfare_family_eliminated_01}", familyNamePtr);

        // Get current family name again
        familyNamePtr = *(char **)getCurrentFamilyNamePtr();
        if (familyNamePtr == nullptr) {
            familyNamePtr = kEmptyString;
        }

        // Build second message: "{f:%s}{$fanfare_family_eliminated_02}"
        stringFormat(&local_30, "{f:%s}{$fanfare_family_eliminated_02}", familyNamePtr);

        // Call Flash: ShowMessage with three arguments
        char *arg1 = local_20 ? local_20 : kEmptyString;
        char *arg2 = local_30 ? local_30 : kEmptyString;
        FlashMethodCall("ShowMessage", 0, gFlashInterface, 3, arg1, arg2, gFanfareFamilyEliminatedText); // DAT_00e2f044

        // Play sound on family data (offset 0x8c)
        playSoundOnFamily((int *)((char *)familyData + 0x8c));

        // Check if unusedString (local_10) is set and call Flash SetImage
        char *tmp = local_10;  // local_10 is uninitialized in decompiled code, but we keep the condition
        if (tmp == nullptr) {
            tmp = kEmptyString;
        }
        if (isStringEmpty(tmp) != 0) {
            FlashMethodCall("SetImage", 0, gFlashInterface, 1, tmp);
        }

        // Set state function pointer at offset 0x7c
        *(int *)((char *)thisPtr + 0x7c) = (int)0x00980bf0; // &LAB_00980bf0

        // Deallocate strings (destructor calls via function pointers)
        // Note: local_4, local_24, local_14 are destructor function pointers stored on stack.
        // We simulate with free().
        if (local_10 != nullptr) {
            free(local_10); // local_4(local_10)
        }
        if (local_30 != nullptr) {
            free(local_30); // local_24(local_30)
        }
        if (local_20 != nullptr) {
            free(local_20); // local_14(local_20)
        }
    }
    return;
}