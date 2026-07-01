// Xbox PDB: EARS_Apt_UIConnections_InitGiverMenu
// FUNC_NAME: DebugMenuManager::populateMenu
void __fastcall DebugMenuManager::populateMenu(int thisPtr)
{
    // Reset menu via global menu handler (DAT_00d861fc)
    FUN_005a04a0("ResetMenu", 0, &DAT_00d861fc, 0);

    int count = *(int *)(thisPtr + 0x80); // +0x80: number of menu items
    for (int i = 0; i < count; i++)
    {
        // Each item entry is an 8-byte structure; first int is a pointer to the item's data
        int itemPtr = *(int *)(*(int *)(thisPtr + 0x68) + i * 8); // +0x68: pointer to array of item entries
        int objectBase;
        if (itemPtr == 0)
        {
            objectBase = 0;
        }
        else
        {
            // Stored pointer is actually object + 0x48; adjust to get base
            objectBase = itemPtr - 0x48;
        }

        // Set temporary fields for this item (likely used by subsequent calls)
        *(int *)(thisPtr + 0x88) = *(int *)(objectBase + 0xB4); // +0xB4: some data (e.g., item ID)
        int dataPtr = objectBase + 0x184;                        // Default offset for data pointer
        if (*(char *)(objectBase + 0x184) == '\0')
        {
            dataPtr = objectBase + 0xC0;                         // Alternate data offset if empty
        }
        *(int *)(thisPtr + 0x84) = dataPtr;                     // +0x84: pointer to item data

        // Convert some identifier (likely a name/string ID) and store
        int nameId = *(int *)(objectBase + 0x164);              // +0x164: string or hash
        *(int *)(thisPtr + 0x94) = FUN_00849e60(nameId);       // +0x94: resolved name/string pointer

        // Add the menu option to the global menu
        FUN_005a04a0("AddMenuOption", 0, &DAT_00d861fc, 0);
    }

    // Finalize menu initialization
    FUN_005a04a0("InitMenu", 0, &DAT_00d861fc, 0);
}