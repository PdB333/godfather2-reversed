// FUNC_NAME: OffsetManager::applyGroupedOffsets
#include <cstdint>

class OffsetManager {
public:
    // +0x0c: Pointer to array of group descriptors (each group: count + base pointer)
    struct GroupDescriptor {
        uint32_t count;   // Number of elements in this group
        int32_t* base;    // Base pointer to array of ints
    } * m_groups;

    // +0x10: Number of groups
    int32_t m_groupCount;

    // +0x14: Constant offset added to group base pointer each iteration
    int32_t m_groupStep;

    // +0x18: Constant offset added to each element value in the group
    int32_t m_elementStep;

    // __fastcall: this in ECX, param2 in EDX (passed as int, modified, returned as part of result)
    uint64_t applyGroupedOffsets(int32_t param2) {
        GroupDescriptor* pGroup = m_groups;
        uint32_t groupIdx = 0;

        if (m_groupCount != 0) {
            do {
                // Shift the base pointer of this group
                pGroup->base += m_groupStep;

                uint32_t elemIdx = 0;
                if (pGroup->count != 0) {
                    do {
                        // Add element offset to each integer in the array
                        pGroup->base[elemIdx] += m_elementStep;
                        // Remember the address of the last element processed
                        param2 = reinterpret_cast<int32_t>(&pGroup->base[elemIdx]);
                        elemIdx++;
                    } while (elemIdx < pGroup->count);
                }

                groupIdx++;
                pGroup++; // advance to next group (2 uint32s per group)
            } while (groupIdx < static_cast<uint32_t>(m_groupCount));
        }

        // This odd return value combines param2 (last element address) with a shifted version of pGroup.
        // The exact semantics are unclear (possibly debug/hash).
        return (static_cast<uint64_t>(param2) << 32) |
               (static_cast<uint64_t>(reinterpret_cast<uintptr_t>(pGroup) >> 8));
    }
};