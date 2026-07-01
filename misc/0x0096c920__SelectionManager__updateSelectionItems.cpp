// FUNC_NAME: SelectionManager::updateSelectionItems
void __fastcall SelectionManager::updateSelectionItems(uint param_1)
{
    int* pItemList;
    int itemCount;
    int iterIndex;
    char cCountValid;
    uint listCount;
    int currentItem;
    uint processedItems;
    uint itemPoolCount;
    uint64_t temp64;
    uint32_t localCount;
    uint32_t localUnused;
    uint64_t tempResult;

    // Get the global selection manager singleton
    SelectionManager* pSel = g_pSelectionManager; // +0x0 (global)
    int* pItemListPtr = (int*)((int)pSel + 0x1b8); // +0x1b8: pointer to item list data

    // Reset output item count for selected items list
    *(int*)((int)pSel + 0x1b0) = 0; // m_selectedItemCount

    localUnused = param_1; // unused parameter stored

    // If item list pointer is null, initialize the list system
    if (*pItemListPtr == 0)
    {
        FUN_0095cf50(); // initItemListSystem?
    }

    tempResult = CONCAT44((uint)tempResult, (uint)(tempResult >> 32)); // noise, likely dead code

    // If the item list manager exists (g_pItemListManager)
    if (g_pItemListManager != 0)
    {
        localCount = 0;
        cCountValid = FUN_0095c8c0(*(int*)((int)pSel + 0x1b8), &localCount); // getListCount
        listCount = localCount;
        tempResult = CONCAT44((uint)tempResult, (uint)(tempResult >> 32));

        if ((cCountValid != '\0') &&
           ((tempResult, listCount < g_maxItems))) // compare listCount < g_maxItems (g_maxItems at 0x01130820)
        {
            g_selectedIndex = 0; // DAT_011307fc = 0
            FUN_009c8f10(g_pItemArray); // freeItemArray
            int itemListMgr = g_pItemListManager;
            g_pItemArray = 0; // DAT_011307f8 = 0
            g_unknown = 0; // DAT_01130800 = 0

            if (g_pItemListManager != 0)
            {
                processedItems = 0;
                itemPoolCount = FUN_0095c950(listCount); // get number of items in pool
                if (itemPoolCount != 0)
                {
                    do
                    {
                        // Access the item data array
                        if ((listCount < *(uint*)(itemListMgr + 8)) &&
                           (currentItem = *(int*)(*(int*)(itemListMgr + 4) + listCount * 4), currentItem != 0))
                        {
                            currentItem = *(int*)(*(int*)(currentItem + 4) + processedItems * 4);
                        }
                        else
                        {
                            currentItem = 0;
                        }
                        // Gather item data from offsets +0x17c and +0x180
                        uint64_t itemData = FUN_0095c290(currentItem + 0x17c, currentItem + 0x180);
                        tempResult = itemData;
                        FUN_0095e000(&tempResult); // push item data into selection list
                        processedItems++;
                    } while (processedItems < itemPoolCount);
                }

                // Save and set the selection state to 2 (e.g., kState_Building)
                uint32_t savedState = *(uint32_t*)((int)pSel + 0xc4);
                *(uint32_t*)((int)pSel + 0xc4) = 2;
                FUN_0095fbc0(2,
                             *(int*)((int)pSel + 0xc8), // m_buildParam1
                             *(int*)((int)pSel + 0xcc)); // m_buildParam2
                FUN_005a04a0("UpdateSelectItem", 0, DAT_00d8cdec, 0); // send event
                *(uint32_t*)((int)pSel + 0xc4) = savedState; // restore
                FUN_0095e7d0(2); // endBuild
                FUN_00966cc0(); // refreshUI
            }
        }
    }

    // Compare global selected index with count of items in selection manager
    if (g_selectedIndex <= *(uint*)((int)pSel + 0x1b0))
    {
        *(int*)((int)pSel + 0x1b4) = 0; // no selected item
        return;
    }

    // Retrieve the selected item from the array (each entry is 8 bytes)
    uint32_t selectedItem = FUN_00962c20(*(int*)(g_pItemArray + *(uint*)((int)pSel + 0x1b0) * 8));
    *(int*)((int)pSel + 0x1b4) = selectedItem; // store selected item
}