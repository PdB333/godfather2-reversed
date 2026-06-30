// FUN_00434940: ChannelManager::clearChannelsInRange
#include <cstdint>

// Forward declarations of helper functions
void FUN_004347e0(void* buffer, int start, int end);
void FUN_00434890(void* buffer, int start, int end);

// Structure representing a channel entry (size 0x30)
struct ChannelEntry {
    int32_t state;        // +0x00: 0=inactive, 1 or 2 active type
    // ... padding up to +0x14
    void* buffer;         // +0x14: pointer to associated buffer
    int32_t bufferCount;  // +0x18: number of elements in buffer
    // total size 0x30
};

// ChannelManager class (partial, based on used members)
class ChannelManager {
public:
    // +0x04: pointer to array of ChannelEntry (stride 0x30)
    ChannelEntry* m_channelArray;
    // m_channelCount is assumed to be loaded into EAX before calling this method
    // (may be a member variable but not directly accessed in this function)
    int32_t m_channelCount;  // offset unknown, used via register EAX
};

// Cleaned reconstruction of FUN_00434940
// This function clears (resets) a range of channels from startIndex to channelCount-1
// channelCount is passed in EAX register (not a standard parameter)
int __thiscall ChannelManager::clearChannelsInRange(uint32_t startChannel, int32_t managerPtr) {
    int32_t channelCount; // originally in_EAX (register variable, set before call)
    // Note: The decompiler shows channelCount as an implied register parameter.
    // It is likely a member variable (e.g., m_channelCount) but not explicitly read from this.
    // For correctness, assume it is passed via EAX.
    if (startChannel < channelCount) {
        int32_t offset = startChannel * 0x30;  // byte offset into channel array
        int32_t remaining = channelCount - startChannel;
        do {
            ChannelEntry* entry = reinterpret_cast<ChannelEntry*>(
                reinterpret_cast<uint8_t*>(this->m_channelArray) + offset);
            int32_t state = entry->state;
            if (state != 0) {
                void* buffer = entry->buffer;
                if (buffer != nullptr) {
                    if (state == 1) {
                        // Type 1: clear buffer from index 0 to bufferCount-1
                        FUN_004347e0(buffer, 0, entry->bufferCount - 1);
                    }
                    else if (state == 2) {
                        // Type 2: different clear operation
                        FUN_00434890(buffer, 0, entry->bufferCount - 1);
                    }
                }
            }
            offset += 0x30;
            remaining--;
        } while (remaining != 0);
    }
    return 1; // success
}