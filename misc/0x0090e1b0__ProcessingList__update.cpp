// FUNC_NAME: ProcessingList::update
// Function at 0x0090e1b0: Updates a processing list of items. Removes items that are either flagged as completed (bit6 set) or satisfy a completion condition.
// +0x11: uint8_t isProcessing (reentrancy flag)
// +0x18: uint** items (array of pointers to items)
// +0x1c: int itemCount
void __fastcall ProcessingList::update(int this) {
    uint32_t* items = *(uint32_t**)(this + 0x18);
    int count = *(int*)(this + 0x1c);
    uint8_t* processingFlag = (uint8_t*)(this + 0x11);

    *processingFlag = 1;                    // Set processing flag

    // Global context for completion checks
    uint32_t* context = (uint32_t*)DAT_01206804;

    if (count == 0) {
        // Empty list: reset global state
        int localData = DAT_0112ffec;
        memClear(&localData, 0);      // FUN_00408a00
        memFree(&DAT_012069c4);       // FUN_004086d0
        *processingFlag = 0;
        return;
    }

    for (uint32_t i = 0; i < count; i++) {
        uint32_t* item = (uint32_t*)items[i];
        bool bit6 = (*item >> 6) & 1;

        if (!bit6) {
            // Not flagged: check completion condition
            updateObject(context);   // FUN_0090da50
            if (isObjectComplete()) { // FUN_0090d7b0
                goto removeItem;
            }
        } else {
removeItem:
            // Remove item: replace with last element
            if (i != count - 1) {
                items[i] = items[count - 1];
            }
            count--;
            onItemRemoved();          // FUN_0090d920
            deleteItem(item);         // FUN_009c8eb0
        }
    }

    finalizeUpdate();                 // FUN_0090df00
    *processingFlag = 0;             // Clear processing flag
}