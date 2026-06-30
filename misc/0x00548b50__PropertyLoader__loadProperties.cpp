// FUNC_NAME: PropertyLoader::loadProperties
// Address: 0x00548b50
// This function iterates through a property data stream (either contiguous block or sparse bitmask-indexed)
// and populates the object's fields at offsets +0x08, +0x0C, +0x10, +0x14, +0x20, +0x24, +0x28, +0x2C
// based on property type IDs (0-4). Initial call to startPropertyBlock validates object type.

#include <cstdint>

// Forward declarations (from other modules)
extern uint32_t g_defaultPropertyValue; // +0x2C default at DAT_00e2b1a4
extern void startPropertyBlock(void* obj, uint32_t typeHash); // FUN_0043aff0
extern void advancePropertyBlock(void** blockPtr, uint32_t& index); // FUN_0043b140

// This method is called from two contexts: mode0 (continuous block) and mode1 (bitmask sparse array)
void PropertyLoader::loadProperties() {
    uint32_t currentIndex;          // uVar4
    void** currentEntry;            // local_8 (mode0) or local_50 (mode1)
    void** entryPtr;                // ppuVar3 -> points to current property entry
    bool exitLoop;                  // bVar5
    uint32_t propertyType;          // puVar2 as integer (truncated from pointer weirdness)
    void* dataValue;                // temp for case4

    // Phase1: Check object type against expected hash (0x6173a1d6 = "PropertyBlock" maybe)
    startPropertyBlock(this, 0x6173a1d6);

    currentIndex = m_currentIndex;  // local_58

    // Main iteration loop
    while (true) {
        // Determine if we should continue based on iteration mode
        if (m_mode == 0) {
            exitLoop = (*m_continuousBlockPtr == nullptr); // local_8 is pointer to current block
        } else {
            exitLoop = (currentIndex == m_totalCount); // local_54 = count
        }
        if (exitLoop) break;

        // Select pointer to current property entry
        if (m_mode == 0) {
            entryPtr = m_continuousBlockPtr; // local_8
        } else {
            entryPtr = &m_sparseEntry; // local_50 (storage for current entry)
        }

        // Extract property type: check if entry has short type field at +6
        if (*(uint16_t*)((uint8_t*)entryPtr + 6) == 0x25E3) {
            // Compact format: type is stored as ushort at [entryPtr+4]? Actually ppuVar3+1
            propertyType = *(uint16_t*)(entryPtr + 1); // cast to pointer arithmetic?
        } else {
            propertyType = (uint32_t)entryPtr[1]; // otherwise type is pointer-sized value
        }

        // Process property based on type (0-4)
        switch (propertyType) {
        case 0: // Property ID 0 -> field at offset +0x08
            if (m_mode == 0) entryPtr = m_continuousBlockPtr;
            else entryPtr = &m_sparseEntry;
            *(void**)((uint8_t*)this + 0x08) = entryPtr[2];
            break;

        case 1: // Property ID 1 -> field at offset +0x0C
            if (m_mode == 0) entryPtr = m_continuousBlockPtr;
            else entryPtr = &m_sparseEntry;
            *(void**)((uint8_t*)this + 0x0C) = entryPtr[2];
            break;

        case 2: // Property ID 2 -> field at offset +0x10
            if (m_mode == 0) entryPtr = m_continuousBlockPtr;
            else entryPtr = &m_sparseEntry;
            *(void**)((uint8_t*)this + 0x10) = entryPtr[2];
            break;

        case 3: // Property ID 3 -> field at offset +0x14
            if (m_mode == 0) entryPtr = m_continuousBlockPtr;
            else entryPtr = &m_sparseEntry;
            *(void**)((uint8_t*)this + 0x14) = entryPtr[2];
            break;

        case 4: // Property ID 4 -> sets a triple of pointers (offset +0x20,+0x24,+0x28) and value at +0x2C
            if (m_mode == 0) entryPtr = m_continuousBlockPtr;
            else entryPtr = &m_sparseEntry;

            // Special handling for compact entry with short size marker
            if (*(uint16_t*)((uint8_t*)entryPtr + 6) == 0x25E3) {
                if (*entryPtr == nullptr) {
                    entryPtr = (void**)(&g_defaultPropertyValue); // fallback to global default pointer array
                } else {
                    // Interpret entry as base+offset: [0] = base, [2] = offset?
                    entryPtr = (void**)((uint8_t*)entryPtr[2] + (intptr_t)*entryPtr);
                }
            } else {
                entryPtr = entryPtr + 2; // skip first two pointers for non-compact
            }

            // Read three values from current entry
            void* p0 = entryPtr[0];
            void* p1 = entryPtr[1];
            void* p2 = entryPtr[2];
            *(void**)((uint8_t*)this + 0x20) = p0;
            *(void**)((uint8_t*)this + 0x24) = p1;
            *(void**)((uint8_t*)this + 0x28) = p2;
            *(uint32_t*)((uint8_t*)this + 0x2C) = g_defaultPropertyValue; // always set to global default
            break;
        }

        // Advance iteration state
        if (m_mode == 0) {
            // Continuous block: advance by block size stored at current block start
            int32_t blockSize = *(int32_t*)*m_continuousBlockPtr;
            if (blockSize < 0) {
                // Negative block size? Maybe indicate end of list; but here it goes to next block
                m_continuousBlockPtr = (void**)((uint8_t*)m_continuousBlockPtr + blockSize);
                advancePropertyBlock(&m_continuousBlockPtr, currentIndex);
                currentIndex = m_currentIndex; // reload after call
            } else if (currentIndex < (m_totalCount - 1)) {
                // Normal advance
                m_continuousBlockPtr = (void**)((uint8_t*)m_continuousBlockPtr + blockSize);
                m_currentIndex = currentIndex + 1;
                currentIndex = m_currentIndex;
            } else {
                // End of continuous list: set to sentinel value (DAT_01163cf8)
                m_continuousBlockPtr = (void**)0x01163cf8;
                m_continuousBlockPtr = (void**)0x01163cf8; // redundant assignment
            }
        } else {
            // Sparse bitmask mode
            m_currentIndex = currentIndex + 1;
            currentIndex = m_currentIndex;
            if (currentIndex != m_totalCount) {
                uint32_t maskByteIndex = currentIndex >> 3;
                uint8_t maskBit = 1 << (currentIndex & 7);
                uint8_t* bitmask = (uint8_t*)m_bitmaskBase; // local_60
                if ((bitmask[maskByteIndex] & maskBit) == 0) {
                    // Entry present: read from data array
                    m_sparseEntry = m_sparseDataPtr; // local_50 <- local_5c
                    m_sparseEntryValue = *m_sparseDataPtr; // local_48 = *local_5c
                    m_sparseDataPtr++; // local_5c++
                } else {
                    // Entry absent: mark as null/zero
                    m_sparseEntry = nullptr;
                    m_sparseEntryValue = 0;
                }
            }
        }
    }
    return;
}