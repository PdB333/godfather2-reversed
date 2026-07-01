// Xbox PDB: EARS_Apt_HonorsScreen_PopulateOn
// FUNC_NAME: ScoreboardScreen::populateHonorRows
void ScoreboardScreen::populateHonorRows(int* pValue, char* pNameBuf, char* pDataBuf, char* pHelpBuf) {
    char* localizedStr = nullptr;
    void (*deallocFunc)(char*) = nullptr;

    for (uint i = 0; i < 0x120; i += 0x18) {
        unsigned int resourceId;
        if (s_honorLocked[i/0x18] == '\0') {
            resourceId = 0;
        } else {
            resourceId = *(unsigned int*)((int)&DAT_00e5661c + i);  // +0x14? Actually offset 0x14 from base? Might be another field
        }

        // Retrieve localized string (e.g., from string table)
        getLocalizedString(resourceId, &localizedStr, 1);

        // Copy the raw value from the static table
        *pValue = *(int*)((int)&DAT_00e56608 + i); // s_honorValues[i/0x18]

        // Copy the name string (predefined)
        copyStringToBuffer(pNameBuf, *(char**)((int)&PTR_s__mp_finalscore_top_player_00e56610 + i), 0x80, 0);

        // Copy the localized data string (or default placeholder)
        char* dataStr = localizedStr;
        if (localizedStr == nullptr) {
            dataStr = &DAT_0120546e; // Default empty string
        }
        copyStringToBuffer(pDataBuf, dataStr, 0x80, 0);

        // Copy the help string
        copyStringToBuffer(pHelpBuf, *(char**)((int)&PTR_s__mp_finalscore_top_player_help_00e56614 + i), 0x80, 0);

        // Determine row type and add to UI
        if (s_honorLocked[i/0x18] == '\0') {
            addHonorRowToUI("AddHonorLockedRow", 0, &g_honorTable, 0);
        } else {
            addHonorRowToUI("AddHonorRow", 0, &g_honorTable, 0);
        }
    }

    // Finalize the table
    addHonorRowToUI("RowsAdded", 0, &g_honorTable, 0);

    // Cleanup localized string if allocated
    if (localizedStr != nullptr) {
        deallocFunc(localizedStr);
    }
}