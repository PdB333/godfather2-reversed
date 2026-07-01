// Xbox PDB: EARS_Apt_UIConnections_InitJobTaskMenu
// FUNC_NAME: MenuManager::resetMenu
void __thiscall MenuManager::resetMenu(int this) {
    int count;             // count of menu items (this+0x78)
    int arrayPtr;          // pointer to item array (this+0x5c)
    int itemPtr;           // base of the current item object
    int iconId;            // icon resource ID retrieved
    int i;                 // loop index

    // Log "ResetMenu" event
    uiManagerLog("ResetMenu", 0, &DAT_00d861fc, 0);

    i = 0;
    count = *(int *)(this + 0x78);
    arrayPtr = *(int *)(this + 0x5c);

    if (0 < count) {
        do {
            // Each element in array is a pointer (8 bytes)
            itemPtr = *(int *)(arrayPtr + i * 8);
            if (itemPtr == 0) {
                itemPtr = 0;
            }
            else {
                // Subtract 0x48 to get base of the object (likely a menu option object)
                itemPtr = itemPtr - 0x48;
            }

            // Set menu's current option data (this+0x88 = some ID from option+0xB4)
            *(int *)(this + 0x88) = *(int *)(itemPtr + 0xB4);
            // Set menu's current option pointer (this+0x84 = pointer to option's label/string at +0x70)
            *(int *)(this + 0x84) = itemPtr + 0x70;
            // Retrieve icon/asset ID from option's field at +0x164
            iconId = getOptionIconId(*(int *)(itemPtr + 0x164));
            *(int *)(this + 0x94) = iconId;

            // Log "AddMenuOption" event
            uiManagerLog("AddMenuOption", 0, &DAT_00d861fc, 0);

            i = i + 1;
        } while (i < count);
    }

    // Log "InitMenu" event (finalize menu)
    uiManagerLog("InitMenu", 0, &DAT_00d861fc, 0);
}