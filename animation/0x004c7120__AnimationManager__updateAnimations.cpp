// FUNC_NAME: AnimationManager::updateAnimations
void AnimationManager::updateAnimations() {
    // this[0] = m_mode, this[1] = m_currentIndex, this[2] = m_lastProcessedIndex
    // this[0x28] = m_entryCount, this[0x29] = m_entries (array of Entry, size 0x1c each)
    if (m_lastProcessedIndex == m_currentIndex || m_mode == 2) {
        return;
    }

    uint entryIndex = 0;
    if (m_entryCount != 0) {
        int offset = 0;
        do {
            Entry* entry = reinterpret_cast<Entry*>(m_entries + offset);
            // entry->m_object is a pointer to some object with a byte at +0xB2
            if ((*(reinterpret_cast<uint8*>(entry->m_object) + 0xB2) & 1) != 0) {
                // Check if the selected pointer (based on parity of m_currentIndex) is non-null
                int* selectedPtr = entry->m_ptrs[(m_currentIndex & 1) + 5]; // +0x14 or +0x18
                if (selectedPtr != nullptr) {
                    setAnimationActive(entry->m_targetObject, 1); // FUN_00459b30

                    // Check a condition on the target object's sub-object
                    // targetObject->someField (+0x50) points to another object with byte at +0x2F
                    if (*(reinterpret_cast<char*>(*(reinterpret_cast<int*>(entry->m_targetObject) + 0x50) + 0x2F) == '\0') {
                        return;
                    }

                    int copyCount = entry->m_copyCount; // +0x0C
                    int basePtr = getAnimationDataBuffer(); // FUN_0060bd50
                    int copyIndex = entry->m_copyIndex; // +0x10

                    // Select one of two pointers at targetObject+0x64 based on byte at subObject+0x2D
                    uint8 xorFlag = *(reinterpret_cast<uint8*>(*(reinterpret_cast<int*>(entry->m_targetObject) + 0x50) + 0x2D) ^ 1;
                    int* destPtr = reinterpret_cast<int*>(entry->m_targetObject + 0x64 + xorFlag * 4); // +0x64 or +0x68

                    int* srcPtr = reinterpret_cast<int*>(getAnimationSourceData()); // FUN_0060bdb0

                    // Copy 3 dwords from source (stride 5 dwords) to destination (stride 3 dwords)
                    int* dest = reinterpret_cast<int*>(basePtr + copyIndex * 4);
                    for (int i = 0; i < copyCount; i++) {
                        dest[0] = srcPtr[0];
                        dest[1] = srcPtr[1];
                        dest[2] = srcPtr[2];
                        dest += 3;
                        srcPtr += 5;
                    }

                    // Post-process the first selected pointer (destPtr)
                    if (*(reinterpret_cast<char*>(destPtr + 7) == '\0') {
                        *(reinterpret_cast<char*>(destPtr + 0x1D) = 0;
                    } else {
                        // Call virtual function at vtable+0x30 on the object pointed by destPtr
                        (**(reinterpret_cast<void(**)(int*)>(*destPtr + 0x30)))(destPtr);
                    }

                    // Post-process the second selected pointer (selectedPtr)
                    if (*(reinterpret_cast<char*>(selectedPtr + 7) == '\0') {
                        *(reinterpret_cast<char*>(selectedPtr + 0x1D) = 0;
                    } else {
                        (**(reinterpret_cast<void(**)(int*)>(*selectedPtr + 0x30)))(selectedPtr);
                    }
                }
            }
            offset += sizeof(Entry); // 0x1C
            entryIndex++;
        } while (entryIndex < m_entryCount);
    }
    m_lastProcessedIndex = m_currentIndex;
}