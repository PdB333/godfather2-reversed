// FUN_NAME: PacketWindowManager::discardFrom
// Address: 0x00668920
// Role: Discards all slots from a given sequence number onward, freeing their usage.
// Used in reliable packet window management (TNL-style). Clears the bitmap from
// the group containing 'sequence' to the end. Resets everything if sequence==0.

class PacketWindowManager {
public:
    // Structure (offsets relative to this):
    // +0x00: int m_groupCount;          // number of groups (each group has 28 slots)
    // +0x04: int m_bitmapWordCount;     // number of uint32 entries in m_bitmap
    // +0x08: int m_freeCount;           // maybe count of free slots (set to 0 on reset)
    // +0x0C: uint32_t* m_bitmap;        // pointer to bitmap array

    int discardFrom(uint32_t sequence) {
        // If sequence == 0, reset the entire allocator
        if ((int)sequence < 1) {
            this->m_freeCount = 0;
            this->m_groupCount = 0;
            memset(this->m_bitmap, 0, this->m_bitmapWordCount * sizeof(uint32_t));
            return 0;
        }

        // Check if sequence is beyond total capacity
        if (this->m_groupCount * 28u < sequence) {
            return lockMutex();  // error path, returns nonzero on failure
        }

        auto err = lockMutex();  // acquire lock
        if (err == 0) {
            uint32_t wordIdx = sequence / 28;
            uint32_t bitInWord = sequence % 28;

            // Clear all bitmap words from (wordIdx+1) onward
            for (uint32_t i = wordIdx + 1; i < this->m_groupCount; i++) {
                this->m_bitmap[i] = 0;
            }

            // Clear bits from bitInWord upward in the current word
            uint32_t mask = (1u << bitInWord) - 1u;
            this->m_bitmap[wordIdx] &= mask;

            unlockMutex();  // release lock
            return 0;
        }
        return err;
    }

private:
    // Declared as extern functions in the binary; likely platform mutex helpers.
    int lockMutex();
    void unlockMutex();
};