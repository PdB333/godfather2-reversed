// FUN_NAME: FilterList::transferMatchingItems

// Reconstructed C++ for function at 0x00462880
// This function iterates over items in 'this' list (m_items) and moves matching items
// from sourceList to destList. Matching criteria: direct ID match (this->m_targetId == item->m_id)
// or item's sub-list contains this->m_secondaryId.
// Uses a global mutex (DAT_00e2e3d4) for thread safety.

void FilterList::transferMatchingItems(void* sourceList, void* destList) {
    // Lock global mutex
    lockMutex(&s_globalMutex); // DAT_00e2e3d4

    uint32_t itemCount = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(this) + 0x14);
    uint32_t index = 0;

    if (itemCount != 0) {
        do {
            // Current filter item
            void* filterItem = *reinterpret_cast<void**>(
                *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x10) + index * 4
            );

            // Check if filterItem matches by direct ID
            if (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0xc) ==
                *reinterpret_cast<int*>(reinterpret_cast<char*>(filterItem) + 0x8)) {
                goto Found;
            }

            // Check if filterItem's sub-list contains our secondary ID
            int subCount = *reinterpret_cast<int*>(reinterpret_cast<char*>(filterItem) + 0x44);
            if (subCount > 0) {
                int* subArray = *reinterpret_cast<int**>(reinterpret_cast<char*>(filterItem) + 0x48);
                for (int j = 0; j < subCount; j++) {
                    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x8) == subArray[j]) {
                        goto Found;
                    }
                }
            }
            goto Next;

        Found:
            // Look for filterItem in sourceList (if provided)
            int foundIndex = -1;
            if (sourceList != nullptr) {
                uint32_t srcCount = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(sourceList) + 0x1c);
                if (srcCount != 0) {
                    void** srcArray = *reinterpret_cast<void***>(reinterpret_cast<char*>(sourceList) + 0x18);
                    for (uint32_t k = 0; k < srcCount; k++) {
                        if (srcArray[k] == filterItem) {
                            foundIndex = static_cast<int>(k);
                            break;
                        }
                    }
                }
            }

            if (foundIndex >= 0 || sourceList == nullptr) {
                // Notify removal (reference count decrement? )
                notifyRemoval(filterItem); // FUN_005707f0

                // Remove from sourceList if found
                if (sourceList != nullptr) {
                    uint32_t srcCount = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(sourceList) + 0x1c);
                    if (static_cast<uint32_t>(foundIndex) != srcCount - 1) {
                        // Swap with last element
                        *reinterpret_cast<void**>(
                            *reinterpret_cast<int*>(reinterpret_cast<char*>(sourceList) + 0x18) + foundIndex * 4
                        ) = *reinterpret_cast<void**>(
                            *reinterpret_cast<int*>(reinterpret_cast<char*>(sourceList) + 0x18) + (srcCount - 1) * 4
                        );
                    }
                    *reinterpret_cast<int*>(reinterpret_cast<char*>(sourceList) + 0x1c) = static_cast<int>(srcCount - 1);
                }

                // Add to destList if provided
                if (destList != nullptr) {
                    // Check capacity
                    int destCount = *reinterpret_cast<int*>(reinterpret_cast<char*>(destList) + 0x1c);
                    int destCapacity = *reinterpret_cast<int*>(reinterpret_cast<char*>(destList) + 0x20);
                    if (destCount == destCapacity) {
                        int newCapacity = (destCapacity == 0) ? 1 : destCapacity * 2;
                        resizeContainer(destList, newCapacity); // FUN_004630a0
                    }

                    // Add filterItem to end of destList
                    void** destArray = *reinterpret_cast<void***>(reinterpret_cast<char*>(destList) + 0x18);
                    destArray[destCount] = filterItem;
                    *reinterpret_cast<int*>(reinterpret_cast<char*>(destList) + 0x1c) = destCount + 1;

                    // Notify addition (reference count increment? )
                    notifyAddition(filterItem); // FUN_00570790

                    // Notify container state change via embedded manager (destList+0x10)
                    void* manager = *reinterpret_cast<void**>(reinterpret_cast<char*>(destList) + 0x10);
                    notifyManager(manager, filterItem); // FUN_00462ae0(*(int*)(manager+0x20))
                }
            }

        Next:
            index++;
        } while (index < itemCount);
    }

    // Unlock global mutex
    unlockMutex(&s_globalMutex); // FUN_00ab4e70
}