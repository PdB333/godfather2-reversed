// FUNC_NAME: ActionQueue::checkFrontItem
void __thiscall ActionQueue::checkFrontItem(void)
{
    ActionItem* pCurrentItem = *(ActionItem**)((int)this + 0xc);  // +0xc: pointer to current item in queue
    ActionItem* pEnd = *(ActionItem**)((int)this + 0x8);         // +0x8: pointer to end of queue

    // If queue is empty or pointer invalid, do nothing
    if (pEnd <= pCurrentItem || pCurrentItem == nullptr)
        return;

    // Check item type: only type 3 directly allowed; type 4 requires validation
    if (pCurrentItem->type != 3)
    {
        if (pCurrentItem->type != 4)
            return;

        int validationResult = validateAction(this);  // FUN_00636850 – validates the action
        if (validationResult == 0)
            return;
    }

    // Read the float value (e.g., priority or weight) from the item
    float itemValue = pCurrentItem->value;   // +4: float field in ActionItem

    // Round to integer and check if it's 0 or 1 (low scores)
    int roundedValue = (int)(itemValue + 0.5f);   // approximate ROUND()
    if ((unsigned int)roundedValue < 2)
    {
        onLowPriorityAction();   // FUN_004582c0 – handles low-priority items
    }
}