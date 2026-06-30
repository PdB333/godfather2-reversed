// FUNC_NAME: Container::clearAndDeallocateItems
void __fastcall Container::clearAndDeallocateItems(void* this)
{
    // this points to a Container structure:
    // +0x00: m_pItems (ItemEntry*)
    // +0x04: m_nCount (int) - number of entries
    // +0x08: m_nCapacity (int) - allocated capacity (unused here except zeroing)

    int countMinusOne = m_nCount - 1;
    if (countMinusOne >= 0) {
        int stride = countMinusOne * sizeof(ItemEntry); // 16 bytes per entry
        do {
            ItemEntry* entry = reinterpret_cast<ItemEntry*>(m_pItems + stride);
            void* object = entry->pObject;
            if (object != nullptr) {
                // Call destructor function pointer stored at offset +0x0C
                entry->destructor(object);
            }
            countMinusOne--;
            stride -= sizeof(ItemEntry);
        } while (countMinusOne >= 0);
    }
    m_nCount = 0;
    freeArrayMemory(m_pItems); // FUN_009c8f10 - frees the array buffer
    m_pItems = nullptr;
    m_nCapacity = 0;
}