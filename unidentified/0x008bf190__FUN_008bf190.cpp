// FUNC_NAME: SomeClass::findFirstSuitableIndex
// Function address: 0x008bf190
// Searches for the first item (index < m_itemCount) whose value meets or exceeds a threshold.
// Returns index on success, 0xFFFFFFFF if no item qualifies.
// Offsets: +0x1a8 = m_itemCount (number of items)
// Callees: 0x00791750 = getThreshold(), 0x008c8170 = getCurrentItemValue()

#include <cstdint>

class SomeClass {
public:
    uint32_t __thiscall findFirstSuitableIndex() {
        int32_t threshold = getThreshold();
        uint32_t index = 0;
        if (m_itemCount != 0) {
            do {
                int32_t itemValue = getCurrentItemValue();
                if (threshold <= itemValue) {
                    return index;
                }
                ++index;
            } while (index < m_itemCount);
        }
        return 0xFFFFFFFF;
    }

private:
    // Offset +0x1a8
    uint32_t m_itemCount; // Number of items in some collection
};

// External helper functions (exact signatures unknown)
int32_t __cdecl getThreshold();          // Returns the threshold value
int32_t __cdecl getCurrentItemValue();   // Returns a value for the current iteration (may depend on internal state)