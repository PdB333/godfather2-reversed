// FUNC_NAME: UIHighlightManager::clearHighlightByType
void UIHighlightManager::clearHighlightByType(void* thisPtr)
{
    // thisPtr is a pointer to the current highlight manager state
    // Layout of this object:
    // +0x00: uint highlightType (either kHighlightFocus or kHighlightHover)
    // +0x04: HighlightContext* context (object containing highlight data)

    uint highlightType = *(uint*)thisPtr;                     // *param_1
    HighlightContext* context = *(HighlightContext**)((uint)thisPtr + 4); // param_1[1] iVar1

    if (!context)
        return;

    // Get the target item ID from the context
    // context layout:
    // +0x0C: GameItem* pItem; (not used directly if null)
    // +0x08: uint somethingFlag;
    // +0x10: uint subHighlightIndex; (only for kHighlightHover)
    GameItem* pItem = (GameItem*)context->pItemOrSomething; // *(int*)(iVar1 + 0xC)
    uint itemId;
    if (pItem == NULL)
    {
        itemId = 0;
    }
    else
    {
        itemId = *(uint*)((uint)pItem + 0x1C); // some ID field at offset 0x1C
    }

    // Hash table lookup using global highlight table
    // DAT_012053b0 points to a structure:
    // +0x00: uint** ppTable (pointer to array of linked list heads)
    // +0x04: uint tableSize
    uint tableSize = DAT_012053b0[1];
    uint** ppTable = (uint**)DAT_012053b0[0];
    uint bucketIndex = itemId % tableSize;
    HighlightNode* node = (HighlightNode*)ppTable[bucketIndex];

    while (node != NULL)
    {
        if (node->itemId == itemId)
            break;
        node = node->next; // node[4] is the next pointer
    }

    if (node == NULL)
        return;

    // Now process based on highlight type
    if (highlightType == kHighlightFocus) // DAT_01206778
    {
        // For focus type, bit 0 of flags indicates active focus highlight
        if ((node->flags & 1) != 0)
        {
            removeHighlight(node, 0); // FUN_00421040(node, 0)
            node->flags &= ~1;
        }
    }
    else if (highlightType == kHighlightHover) // DAT_012067b4
    {
        // For hover type, the specific sub-index is stored in context+0x10
        uint subIndex = context->subHighlightIndex; // *(int*)(iVar1 + 0x10)
        uint mask = 1 << (subIndex & 0x1F);

        if ((node->flags & mask) != 0)
        {
            removeHighlight(node, subIndex); // FUN_00421040(node, subIndex)
            node->flags &= ~mask;
        }

        // If all highlights are cleared, call cleanup/redraw functions
        if (node->flags == 0)
        {
            updateHighlightSystem(); // FUN_004217c0
            refreshDisplay();       // FUN_00420ff0
        }
        else if (context->somethingFlag == 0) // *(int*)(iVar1 + 8)
        {
            context->somethingFlag = 1;
            return;
        }
    }
}