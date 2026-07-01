//FUNC_NAME: SomeManager::rebuildItemList
void __thiscall SomeManager::rebuildItemList(void)
{
    int savedItemValue;
    int *itemArray;
    uint itemCount;
    int i;
    int newCapacity;
    int *newArray;
    int sourceIndex;
    void *sourceCollection;
    uint collectionSize;
    void *collectionItem;
    int itemId;

    // Save the current item value if there is a valid current index
    if (m_currentIndex == -1) {
        savedItemValue = -1;
    } else {
        savedItemValue = m_pItemArray[m_currentIndex];
    }

    // Reset current index and item count
    m_currentIndex = -1;
    if (m_itemCount != 0) {
        m_itemCount = 0;
    }

    // If there is a valid source index, rebuild the list from the source collection
    if ((m_sourceIndex != -1) &&
        (sourceCollection = GetCollectionFromSource(m_pSourceArray[m_sourceIndex]),
         sourceCollection != nullptr) &&
        (collectionSize = *(uint *)((int)sourceCollection + 8), collectionSize != 0)) {
        for (i = 0; i < collectionSize; i++) {
            collectionItem = GetCollectionItem(i);
            if (collectionItem != nullptr) {
                itemId = *(int *)((int)collectionItem + 0x38);
                // Grow the array if needed
                if (m_itemCount == m_itemCapacity) {
                    newCapacity = (m_itemCapacity == 0) ? 1 : m_itemCapacity * 2;
                    ReallocateArray(newCapacity);
                }
                // Add item to the array
                itemArray = m_pItemArray;
                m_itemCount++;
                itemArray[m_itemCount - 1] = itemId;
                // Update current index if this item matches the saved value
                if (savedItemValue == itemId) {
                    m_currentIndex = m_itemCount - 1;
                }
            }
        }
    }

    // Ensure current index is valid after rebuild
    if ((m_itemCount != 0) &&
        ((m_itemCount < m_currentIndex) || (m_currentIndex == -1))) {
        m_currentIndex = 0;
    }
}