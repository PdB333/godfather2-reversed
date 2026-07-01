// FUNC_NAME: FloatTableSearch::findNextGEQ
// Function at 0x008a39c0
// Searches a global sorted float table (g_tableFloats) for the first element >= m_key,
// starting from a global cursor (g_searchCursor) that increments as we search.
// The struct at param_1 (this) has fields:
//   +0x4: m_count (number of elements to consider)
//   +0x8: m_max   (maximum number of elements)
//   +0xC: m_key   (the float key to find)
// Global state:
//   g_tableFloats (DAT_010c2680) - base of float array
//   g_tableMask   (DAT_010c2678) - bitmask to wrap index (likely array size - 1)
//   g_searchCursor (DAT_012054b4) - persistent index for the search

#include <cstdint>

// Global table data (externally defined)
extern float* g_tableFloats;      // DAT_010c2680
extern uint32_t g_tableMask;      // DAT_010c2678
extern uint32_t g_searchCursor;   // DAT_012054b4

struct FloatTableSearchParams {
    uint32_t m_count;   // offset 0x4
    uint32_t m_max;     // offset 0x8
    float m_key;        // offset 0xC
};

uint32_t __fastcall FloatTableSearch::findNextGEQ(FloatTableSearchParams* this) {
    uint32_t result = 0;
    // cap the count to m_max
    uint32_t maxCount = this->m_count + 2;
    if (maxCount > this->m_max) {
        maxCount = this->m_max;
    }
    uint32_t cursor = g_searchCursor;

    // Process 4 elements per iteration (unrolled loop)
    if (maxCount > 3) {
        do {
            // Check first element of block
            if (this->m_key <= g_tableFloats[g_tableMask & cursor]) {
                g_searchCursor = cursor + 1;
                return result;
            }
            g_searchCursor = cursor + 2;
            // Check second element
            if (this->m_key <= g_tableFloats[g_tableMask & (cursor + 1)]) {
                return result + 1;
            }
            g_searchCursor = cursor + 3;
            // Check third element
            if (this->m_key <= g_tableFloats[g_tableMask & (cursor + 2)]) {
                return result + 2;
            }
            cursor += 4;
            // Check fourth element
            if (this->m_key <= g_tableFloats[g_tableMask & (cursor - 1)]) {
                g_searchCursor = cursor;
                return result + 3;
            }
            result += 4;
            g_searchCursor = cursor;
        } while (result < maxCount - 3);
    }

    // Handle remaining elements (0 to 3)
    if (result < maxCount) {
        while (true) {
            uint32_t idx = g_tableMask & g_searchCursor;
            g_searchCursor++;
            if (this->m_key <= g_tableFloats[idx]) {
                break;
            }
            result++;
            if (result >= maxCount) {
                return result;
            }
        }
    }
    return result;
}