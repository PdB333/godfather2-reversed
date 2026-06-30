// FUNC_NAME: SomeManager::resetAllSlots
// Address: 0x00569190
// Role: Iterates over all slots, resetting active flags and releasing sub-items.
// Offsets:
//   +0x000: vtable pointer
//   +0x228: array of pointers to slot structures
//   +0x328: count of slot structures (max 64)
// Each slot structure:
//   +0x000: unused/padding (first element skipped)
//   +0x004: array of item pointers (starting at offset 4)
//   +0x104: count of items
// Each item structure:
//   +0x128: byte flag (set to 1 to mark as active)
//   +0x12c: array of sub-item pointers (size 300 decimal = 0x12c)
//   +0x14c: count of sub-items

void __fastcall SomeManager::resetAllSlots(SomeManager* this)
{
    uint slotIndex = 0;
    this->vtable = &g_SomeManagerVtable; // Set vtable to global table

    if (this->slotCount != 0)
    {
        // slotArray is at offset 0x228
        SlotData** slotArrayPtr = reinterpret_cast<SlotData**>(reinterpret_cast<uint8*>(this) + 0x228);
        do
        {
            SlotData* slotData = *slotArrayPtr;
            uint itemIndex = 0;

            if (slotData->itemCount != 0)
            {
                // itemArray starts at offset 4 of slotData (skipping first word)
                int** itemPtrPtr = reinterpret_cast<int**>(reinterpret_cast<uint8*>(slotData) + 4);
                do
                {
                    int* currentItem = *itemPtrPtr;
                    // Set active flag at offset 0x128
                    *reinterpret_cast<uint8*>(currentItem + 0x128) = 1;

                    if (currentItem->subItemCount != 0)
                    {
                        uint subItemIndex = 0;
                        // subItemArray at offset 0x12c (300 decimal)
                        void** subItemPtr = reinterpret_cast<void**>(reinterpret_cast<uint8*>(currentItem) + 0x12c);
                        do
                        {
                            releaseSubItem(*subItemPtr); // Release each sub-item
                            subItemIndex++;
                            subItemPtr++;
                        } while (subItemIndex < currentItem->subItemCount);
                    }
                    currentItem->subItemCount = 0; // Clear sub-item count
                    itemIndex++;
                    itemPtrPtr++;
                } while (itemIndex < slotData->itemCount);
            }
            slotIndex++;
            slotArrayPtr++;
        } while (slotIndex < this->slotCount);
    }
}