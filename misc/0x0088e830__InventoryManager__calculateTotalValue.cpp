// FUNC_NAME: InventoryManager::calculateTotalValue
// Address: 0x0088e830
// Role: Iterates over the inventory item list (stored by IDs), resolves each item pointer,
//       checks if the item is active/in-use, and accumulates a numeric value (likely cost or weight).
int __fastcall InventoryManager::calculateTotalValue(InventoryManager* thisPtr)
{
    int* itemPtr;                  // piVar1
    int itemProperty;              // local_4
    int totalValue;                // local_8
    int itemIndex;                 // uVar4
    uint itemCount;                // uVar3 : total items = byte[0x80] + byte[0x81]
    int result;                    // iVar2

    // The inventory stores the count in two bytes at +0x80 and +0x81 (likely low/high or separate lists)
    itemCount = (uint)(thisPtr->countLow) + (uint)(thisPtr->countHigh);
    totalValue = 0;
    itemIndex = 0;
    result = 0;

    if (itemCount != 0)
    {
        do
        {
            // Retrieve item pointer from ID stored in array at +0x68
            // The array element is an item ID (or handle) resolved by getItemPointer
            itemPtr = (int*)getItemPointer(*(int*)(thisPtr->itemIDArray + itemIndex * 4));
            if ((itemPtr != nullptr) && (*itemPtr != 0))
            {
                // Extract a property from the item (e.g., +0x08 might be a status or type)
                itemProperty = itemPtr[2]; // offset +0x08 (since int*)
                // Check if the item is active (or has a required flag)
                result = isItemActive(&itemProperty);
                if (result != 0)
                {
                    // Retrieve the numeric value for this item (e.g., cost, weight)
                    result = getItemValue();
                    totalValue += result;
                }
            }
            itemIndex++;
            result = totalValue;
        } while (itemIndex < itemCount);
    }

    return result;
}