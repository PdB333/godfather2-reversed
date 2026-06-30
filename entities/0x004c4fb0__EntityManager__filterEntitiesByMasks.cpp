// FUNC_NAME: EntityManager::filterEntitiesByMasks
// Function at 0x004c4fb0 - Filters entities based on a byte mask and a word mask.
// This is a member function (__thiscall) on an entity manager class.
// Parameter: combinedMask - low byte is byteMask, high byte (>>8) is wordMask.
// Result: outputs indices of matching entities into m_filterResultIndices array and sets m_filterResultCount.

#include <cstdint>

// Assumed structure offsets:
// +0x08: uint8_t* m_byteMaskArray (array of byte flags per entity)
// +0x0C: uint16_t* m_wordMaskArray (array of word flags per entity)
// +0x14: uint16_t* m_indirectIndexList (when m_useIndirectList != 0)
// +0x1A: uint16_t m_filterResultCount
// +0x1C: uint16_t* m_filterResultIndices (output array)
// +0x38: uint32_t m_totalEntityCount (number of entries in direct arrays)
// +0x3C: uint8_t m_useIndirectList (flag: if 0, iterate over direct indices; else iterate over indirect list)

void EntityManager::filterEntitiesByMasks(uint32_t combinedMask) {
    uint8_t byteMask = combinedMask & 0xFF;
    uint16_t wordMask = (uint16_t)((combinedMask >> 8) & 0xFFFF);

    uint16_t resultCount = 0;
    uint16_t index;

    if (m_useIndirectList == 0) {
        // Direct iteration over all entity indices
        for (uint16_t i = 0; i < m_totalEntityCount; i++) {
            uint32_t currentIndex = i;
            if ( (m_byteMaskArray[currentIndex] & byteMask) == byteMask &&
                 (m_wordMaskArray[currentIndex] & wordMask) == wordMask ) {
                m_filterResultIndices[resultCount] = i;
                resultCount++;
            }
            // The original code has a safety check for index overflow (currentIndex == 0xFFFFFFFF) which is dead code here.
        }
    } else {
        // Iterate over indirect list (terminated by 0xFFFF)
        uint32_t listPos = 0;
        while (true) {
            index = m_indirectIndexList[listPos];
            if (index == 0xFFFF) {
                break;
            }
            if (index >= m_totalEntityCount) {
                break; // Safety, though original code didn't check
            }
            if ( (m_byteMaskArray[index] & byteMask) == byteMask &&
                 (m_wordMaskArray[index] & wordMask) == wordMask ) {
                m_filterResultIndices[resultCount] = index;
                resultCount++;
            }
            listPos++;
        }
    }
    m_filterResultCount = resultCount;
}