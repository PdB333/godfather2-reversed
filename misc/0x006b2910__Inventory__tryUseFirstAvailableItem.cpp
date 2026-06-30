// FUNC_NAME: Inventory::tryUseFirstAvailableItem
void __thiscall Inventory::tryUseFirstAvailableItem(Inventory* thisPtr)
{
    int itemType;               // field at +0x194
    int* slotArray;             // base of 4 slots at +0x184
    int slotIndex;              // index to check
    int* item;
    bool hasAnyItem;

    itemType = *(int*)((uint)thisPtr + 0x194);
    slotArray = (int*)((uint)thisPtr + 0x184);

    // Only act if the inventory is of a type that allows item use (0 = empty, 0x48 = equipped)
    if ((itemType == 0 || itemType == 0x48) &&
        (*(int*)(slotArray + 0) != 0 ||            // +0x184
         *(int*)(slotArray + 1) != 0 ||            // +0x188
         *(int*)(slotArray + 2) != 0 ||            // +0x18c
         *(int*)(slotArray + 3) != 0))             // +0x190
    {
        // Get the item in the first slot (index 0)
        item = (int*)FUN_00446100(slotArray, 0);   // likely inventorySlot::getItem
        if (item != nullptr)
        {
            FUN_0044b210(item);                    // likely Item::use or similar
        }
    }
}