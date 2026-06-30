// FUNC_NAME: ItemListProcessor::processAll
// Function at 0x004bc0e0: Iterates over a global item list and processes each entry
// The item list is an array of 32-byte structures (ItemEntry) with default initialization.
// The count of items is obtained via GetItemCountBySize(0x20, &count).
// For each item, it calls processItem(this, &entry) then processItemCleanup(&entry).

struct ItemEntry {
    void* ptr;           // +0x00: Pointer to some global data (initialized to &PTR_LAB_00e35c24)
    int field04;         // +0x04: Initially 0xFFFFFFFF (sentinel)
    int field08;         // +0x08: Initially 0xFFFFFFFF (sentinel)
    int field0C;         // +0x0C: Initially 0
    int field10;         // +0x10: Initially 0xFFFFFFFF (sentinel)
    int field14;         // +0x14: Initially 0xFFFFFFFF (sentinel)
    int field18;         // +0x18: Initially 0
    int field1C;         // +0x1C: Initially 0
}; // size = 32 bytes = 0x20

// External functions (declared for clarity)
void GetItemCountBySize(int size, int* outCount);
void processItem(void* context, ItemEntry* entry);
void processItemCleanup(ItemEntry* entry);

void ItemListProcessor::processAll(void* this) {
    int itemCount;
    ItemEntry entry; // local struct on stack

    // Get the number of items to process (size 0x20 suggests entry size)
    GetItemCountBySize(0x20, &itemCount);

    // Initialize the entry structure with default values from global pointer table
    entry.ptr = (void*)&PTR_LAB_00e35c24; // static global pointer table
    entry.field04 = -1;                  // sentinel
    entry.field08 = -1;                  // sentinel
    entry.field0C = 0;
    entry.field10 = -1;                  // sentinel
    entry.field14 = -1;                  // sentinel
    entry.field18 = 0;
    entry.field1C = 0;

    // Process each item until count reaches zero
    while (itemCount != 0) {
        processItem(this, &entry);
        processItemCleanup(&entry);
        itemCount--;
    }
}