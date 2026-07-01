// FUNC_NAME: Iterator::advance

// Function address: 0x0082d930
// Role: Advances an iterator over a collection of items, handling initialization, wrap-around, and conditional selection.
// The iterator state is stored in the object at param_1:
//   +0x04: m_currentIndex (uint)
//   +0x08: m_items (pointer to array of pointers to items)
//   +0x0c: m_count (int)
// param_2 is returned unchanged (likely a user-provided context or output pointer).
// param_3 is a key used to look up an index via getIndexFromKey.

#include <cstdint>

// Forward declarations of helper functions (from other modules)
void initializeIterator();                          // FUN_008334a0
void resetIterator();                               // FUN_009cbee0
uint32_t getIndexFromKey(uint32_t key);             // FUN_0082d390
void handleInvalidKey();                            // FUN_008295f0
bool checkCondition(uint32_t key, void* item);      // FUN_00835a00
void applyResult(void*** result);                   // FUN_0082d190

// Global sentinel pointer table (used for empty/invalid states)
extern void* g_nullIteratorResult;                  // PTR_LAB_00d7366c

class Iterator {
public:
    uint32_t m_currentIndex;   // +0x04
    void*** m_items;           // +0x08 (pointer to array of pointers to items)
    int32_t m_count;           // +0x0c

    // Returns param_2 unchanged after advancing the iterator.
    uint32_t advance(uint32_t param_2, uint32_t key) {
        void*** result;  // pppuVar5

        if (m_count == 0) {
            // Empty collection: initialize and use sentinel.
            initializeIterator();
            void* localArray[24] = {0}; // local_90
            localArray[0] = &g_nullIteratorResult;
            // local_30 and local_20 are zero-initialized (unused?)
            resetIterator();
            result = localArray;
        }
        else if (m_count == 1) {
            // Single item: get the first element directly.
            result = (void***)*m_items[0]; // dereference the first item pointer
        }
        else {
            uint32_t index = getIndexFromKey(key);
            if (index == 0xFFFFFFFF) {
                handleInvalidKey();
                void* localArray[24] = {0};
                localArray[0] = &g_nullIteratorResult;
                result = localArray;
            }
            else {
                m_currentIndex = index;
                uint32_t nextIndex;
                if (index < (uint32_t)(m_count - 1)) {
                    nextIndex = index + 1;
                }
                else {
                    nextIndex = 0; // wrap around
                }
                void*** nextItem = m_items[nextIndex]; // pointer to item at next index
                void*** currentItem = m_items[index];  // pointer to item at current index
                // Check condition on the next item (offset +4? pppuVar5+1)
                if (checkCondition(key, nextItem + 1)) {
                    result = currentItem; // stay on current
                }
                else {
                    result = nextItem; // advance to next
                }
            }
        }

        applyResult(result);
        return param_2;
    }
};