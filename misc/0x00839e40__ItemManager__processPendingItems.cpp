// FUNC_NAME: ItemManager::processPendingItems
// Function address: 0x00839e40
// Role: Processes a list of pending items (probably objects or handles) by calling a function on each,
// then marks them as processed. Returns a pointer to data at offset +0x20.

struct ItemManager {
    // vtable at +0x00
    char field_0x04[4]; // unknown
    char processed; // +0x08 - flag indicating if the list has been processed
    char field_0x09[7]; // alignment padding
    void** items; // +0x10 - pointer to array of item pointers
    int count; // +0x14 - number of items in the list
    // data area at +0x20 (returned by this function)
};

int __thiscall ItemManager::processPendingItems() {
    uint i;

    if (processed == 0) {
        i = 0;
        if (count != 0) {
            do {
                // Process each item via a separate function
                FUN_00838140(items[i]);
                i++;
            } while (i < count);
        }
        processed = 1; // Mark list as processed
    }
    // Return pointer to the internal data area at offset +0x20
    return (int)(((char*)this) + 0x20);
}