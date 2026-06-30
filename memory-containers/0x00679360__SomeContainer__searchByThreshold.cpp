// FUNC_NAME: SomeContainer::searchByThreshold
// Function address: 0x00679360
// Role: Searches a sorted array of shorts for a given value, returning a combined index-value pair.
// The object has two separate arrays (chosen by param_2) each with its own size and low/high bounds.
// The search is linear on one side based on comparisons. param_1 indicates search direction: 0 for lower_bound, -1 for previous, 1 for next.
// Returns: (index << 16) | short value at that index. If out of bounds, returns ( (size-1)<<16 | last_value ) or 0.

#include <cstdint>

class SomeContainer {
public:
    // Offsets (all shorts):
    // +0x00: m_sizeA
    // +0x02: m_dataA[] (short array)
    // +0x82: m_lowA
    // +0x84: m_highA
    // +0x41: m_sizeB
    // +0x43: m_dataB[]
    // +0x83: m_lowB
    // +0x85: m_highB

    uint32_t searchByThreshold(short dir, short windowId) const {
        short size;
        short high;
        const short* data;
        short low;

        if (windowId == 0) {
            size = *(short*)(this);               // +0x00 m_sizeA
            high = *(short*)((uint8_t*)this + 0x84);  // +0x84 m_highA
            data = (const short*)((uint8_t*)this + 2); // +0x02 m_dataA
            low = *(short*)((uint8_t*)this + 0x82);   // +0x82 m_lowA
        } else {
            size = *(short*)((uint8_t*)this + 0x41);  // +0x41 m_sizeB
            high = *(short*)((uint8_t*)this + 0x85);  // +0x85 m_highB
            data = (const short*)((uint8_t*)this + 0x42); // +0x42 m_dataB
            low = *(short*)((uint8_t*)this + 0x83);   // +0x83 m_lowB
        }

        uint32_t result = (uint32_t)(uint16_t)low;

        if (dir == 0) {
            // Find insertion point: return first element >= low? Actually compare low vs high.
            if ((short)low <= high) {
                if (high <= (short)low) {
                    return result; // exact match? return low value maybe
                }
                dir = -1;
            } else {
                dir = 1;
            }
        }

        if (dir < 0) {
            int idx = size - 1;
            if (idx < 0) {
                return result;
            }
            while (idx >= 0 && (short)low <= data[idx]) {
                idx--;
            }
            idx = idx + 1 + dir; // dir is -1, so idx = (prev index)
            if (idx < 0) {
                idx = 0;
            }
            return ((uint32_t)(uint16_t)idx << 16) | (uint16_t)data[idx];
        } else {
            // dir > 0
            int idx = 0;
            while (idx < size && data[idx] <= (short)low) {
                idx++;
            }
            idx = idx - 1 + dir; // dir is 1, so idx = next index after break (or last)
            if (idx >= size) {
                return ((uint32_t)(uint16_t)(size - 1) << 16) | (uint16_t)data[size - 1];
            }
            return ((uint32_t)(uint16_t)idx << 16) | (uint16_t)data[idx];
        }
    }
};