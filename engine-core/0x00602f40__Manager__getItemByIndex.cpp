// FUNC_NAME: Manager::getItemByIndex
// Function at 0x00602f40: Looks up an item by index from an internal array,
// with default index fallback. Returns a pointer to the item or a sentinel.
//
// Offsets relative to 'this':
//   +0x20: pointer to an ArrayHeader structure (ArrayHeader*)
//   +0x40: default index (uint32)
//
// ArrayHeader structure (pointed to by this+0x20):
//   +0xA8: count of items (uint32)
//   +0xB0: pointer to array of items, each item is 0x60 bytes
void* __thiscall Manager::getItemByIndex(uint itemIndex)
{
    // If index is sentinel (0xFFFFFFFF), use stored default
    if (itemIndex == 0xFFFFFFFF) {
        itemIndex = *(uint*)(this + 0x40);
    }

    // Retrieve the array header
    int* arrayHeader = *(int**)(this + 0x20);
    uint itemCount = *(uint*)(arrayHeader + 0xA8); // +0xA8

    // Bounds check
    if (itemIndex < itemCount) {
        // Pointer to the base of the item array (0xB0)
        int itemArrayBase = *(int*)(arrayHeader + 0xB0);
        // Each item is 0x60 bytes
        return (void*)(itemArrayBase + itemIndex * 0x60);
    }

    // Out-of-range: return sentinel invalid object
    return &DAT_012222c8;
}