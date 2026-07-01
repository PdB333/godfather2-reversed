// FUNC_NAME: BufferManager::insertEntry
// Function address: 0x0083fa00
// EA EARS engine buffer manager method: inserts a 16-byte entry at given index, returns handle with flag.
#include <cstdint>

class BufferManager {
public:
    // Offsets relative to 'this':
    // +0x50: m_usedSlots (int) - highest used slot index + 1 (size)
    // +0x54: m_maxSlots (int) - maximum number of slots
    // +0x58: m_bufferBase (void*) - pointer to array of 16-byte entries

    uint32_t insertEntry(const uint32_t data[4], uint32_t index) {
        // Bounds check: reject if index >= capacity
        if (index >= m_maxSlots) {
            return index & 0xFFFFFF00; // Return index with low byte cleared (invalid handle)
        }

        // Update used slot count to ensure it encompasses the new index
        int32_t newUsed = static_cast<int32_t>(index + 1);
        if (newUsed < m_usedSlots) {
            newUsed = m_usedSlots;
        }
        m_usedSlots = newUsed;

        // Calculate address of the slot (each slot is 0x10 = 16 bytes)
        uint32_t* slot = reinterpret_cast<uint32_t*>(
            reinterpret_cast<uintptr_t>(m_bufferBase) + index * 16
        );

        // Copy 4 dwords from data into the slot
        slot[0] = data[0];
        slot[1] = data[1];
        slot[2] = data[2];
        slot[3] = data[3];

        // Return a handle: slot address with low byte forced to 1 (valid flag)
        return (reinterpret_cast<uintptr_t>(slot) & 0xFFFFFF00) | 1;
    }

private:
    // Actual member variables (layout assumed from offsets)
    int32_t m_usedSlots;   // +0x50
    int32_t m_maxSlots;    // +0x54
    void* m_bufferBase;    // +0x58
};