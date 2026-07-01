// FUNC_NAME: UISelectionManager::updateSelection
// Address: 0x009103c0
// Updates the HUD selection based on controller input, populating selection data fields
// (name, description, cost, extra) from the current item. Handles both single selections and submenus.
// Offsets in this: +0x264 (128-byte string buffer), +0x2e8 (integer selection index/value).

void __fastcall UISelectionManager::updateSelection(UISelectionManager* thisPtr)
{
    int totalEntries = getNumItems();                       // FUN_009bf8f0
    char selectionName[128];                                // local_80
    char selectionDesc[128];                                // local_180
    char selectionCost[128];                                // local_200
    char selectionExtra[128];                               // local_100

    memset(selectionName, 0, sizeof(selectionName));
    memset(selectionDesc, 0, sizeof(selectionDesc));
    memset(selectionCost, 0, sizeof(selectionCost));
    memset(selectionExtra, 0, sizeof(selectionExtra));

    for (int i = 0; i < totalEntries; i++)
    {
        processItemAtIndex(i);                              // FUN_009bf900

        int inputState = getInputState();                   // FUN_009bf470
        if (inputState == 2)                                // Item selected
        {
            int dataHandle = getSelectionFields(selectionName, selectionDesc, selectionCost, selectionExtra);
                                                            // FUN_009bf4c0
            populateSelectionFields(dataHandle, selectionName, selectionDesc, selectionCost, selectionExtra);
                                                            // FUN_0090fd10

            int extraField = getSelectionExtra();           // FUN_009bf4f0
            setSelectionExtra(extraField);                  // FUN_009bf580

            int selectionId = getSelectionId();             // FUN_009bf490
            copySelectionText(&thisPtr->field_0x264, 0x80, &PTR_LAB_00d83b5c, selectionId);
                                                            // FUN_005c4630 – copies formatted text into this+0x264

            sendSelectEvent("SetSelection", 0, &DAT_00d83ad0, 5, &DAT_00e36da0,
                            selectionName, selectionDesc, selectionCost, selectionExtra);
                                                            // FUN_005a04a0 – Lua/script event
        }
        else if (inputState == 6)                           // Submenu opened (e.g., crew list)
        {
            int subCount = getNumSubItems();                // FUN_009bf9f0
            for (int j = 0; j < subCount; j++)
            {
                int subItemData = getSubItemData(j);        // FUN_009bf9a0
                if (subItemData != 0)
                {
                    populateSelectionFields(subItemData, selectionName, selectionDesc, selectionCost, selectionExtra);
                                                            // FUN_0090fd10
                    thisPtr->field_0x2e8 = getSubItemValue(j); // FUN_009bfb70 – stores sub-item index/value
                    sendSelectEvent("SetSelection", 0, &DAT_00d83ad0, 5, &DAT_00e36da0,
                                    selectionName, selectionDesc, selectionCost, selectionExtra);
                                                            // FUN_005a04a0
                }
            }
        }
    }
}