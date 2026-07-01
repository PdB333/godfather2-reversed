// Xbox PDB: EARS_Apt_UIConnections_InitRewardMenu
// FUNC_NAME: DebugMenu::RebuildMenu
// Function at 0x009223c0 - Rebuilds the debug menu by resetting, adding options from a list, and initializing.
// Calls external UI script commands (ResetMenu, AddMenuOption, InitMenu).
// Uses member fields: +0x7c (maxItems), +0x84 (currentItemData pointer), +0x88 (currentItemValue), +0x94 (selectionIndex).
void __thiscall DebugMenu::RebuildMenu( int this )
{
    int iMaxItems;       // max items from member field
    int iItemCount;      // number of items from list
    int iEffectiveCount; // min(iItemCount, iMaxItems)
    int iIndex;          // loop index
    int iItemPtr;        // pointer to current menu item struct

    // Field offsets documented:
    // this+0x7c = int maxMenuItems (capacity)
    // this+0x84 = void* currentItemData (pointer to item data +0x98)
    // this+0x88 = int currentItemValue (copied from item+0x80)
    // this+0x94 = int selectedIndex

    // Issue reset command
    UIScriptCommand( "ResetMenu", 0, sMenuContext, 0 );

    // Retrieve list of available menu items (fills outItemList, outCount, unused)
    // MenuItemList is an array of 8-byte entries; each entry holds a pointer to a MenuItem struct.
    int outItemList = 0;
    int outCount = 0;
    int unused = 0;
    GetAvailableMenuItems( &outItemList );

    iItemCount = outCount;               // local_8
    int pList = outItemList;             // local_c

    // Clear selected index
    *(int *)(this + 0x94) = 0;

    // Determine effective count (clamp to max)
    if ( *(int *)(this + 0x7c) < iItemCount ) {
        iEffectiveCount = *(int *)(this + 0x7c);
    } else {
        iEffectiveCount = iItemCount;
    }

    // Iterate over items and add each as a menu option
    for ( iIndex = 0; iIndex < iEffectiveCount; iIndex++ ) {
        // Each entry in pList is 8 bytes: first 4 bytes is pointer to MenuItem struct
        iItemPtr = *(int *)(pList + iIndex * 8);
        // Copy item value (int at +0x80) to this+0x88
        *(int *)(this + 0x88) = *(int *)(iItemPtr + 0x80);
        // Set current item data pointer to item+0x98
        *(int *)(this + 0x84) = iItemPtr + 0x98;
        // Add the option via UI script
        UIScriptCommand( "AddMenuOption", 0, sMenuContext, 0 );
    }

    // Finalize menu initialization
    UIScriptCommand( "InitMenu", 0, sMenuContext, 0 );

    // Set a flag in global state indicating menu is active/needs redraw
    *(uint16 *)(gGlobalState + 0x102) = *(uint16 *)(gGlobalState + 0x102) | 1;

    // Free the list if it was allocated
    if ( pList != 0 ) {
        FreeMenuItemList( pList );
    }

    return;
}