// FUNC_NAME: selectListItem
void __fastcall selectListItem(int param_1)
{
    // Store the selection value globally (e.g., item ID or index)
    gSelectedItem = param_1;

    // Check if we are in a valid UI context with a populated list
    if (gCurrentUI == &gDefaultUIList &&            // DAT_012058e8 == &DAT_0121b740
        gListItemCount > 1 &&                       // DAT_0121b874 > 1
        gListItemArray[gCurrentItemIndex] != 0)      // &DAT_0121ba84 + DAT_0121b878 * 4
    {
        // Execute the selection action on the target item
        executeSelectionAction(gUIListContext,       // DAT_0121b754
                               gListItemArray[gCurrentItemIndex], // item pointer
                               param_1);             // FUN_0060b2f0(three params)
    }
}