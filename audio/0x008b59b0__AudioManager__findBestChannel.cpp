//FUNC_NAME: AudioManager::findBestChannel
// Function address: 0x008b59b0
// Purpose: Finds the best available audio channel (index with smallest load < 8).
// Uses a global pointer (DAT_0112b9b4) to a structure with extra priority values for channels 0 and 1.

#include <cstdint>

// Forward declaration of helper function (likely returns base load for a channel)
uint32_t getChannelBaseLoad(uint32_t channelIndex);

// Global pointer to a structure containing extra channel data (offsets 0x54, 0x58)
extern uint8_t* gChannelManager; // DAT_0112b9b4

class AudioManager {
public:
    // Offset +0x1b0: number of channels
    uint32_t m_channelCount; // at +0x1b0

    // Returns the index of the best channel (lowest load < 8)
    uint32_t findBestChannel() {
        bool allAboveThreshold = true;
        uint32_t bestIndex = 0;
        uint32_t bestValue = 10; // initial high value (>8)

        // First pass: check if all channels have total load > 7
        if (m_channelCount != 0) {
            for (uint32_t i = 0; i < m_channelCount; ++i) {
                uint32_t baseLoad = getChannelBaseLoad(i);
                int extra = 0;
                if (i < 2) {
                    // Channels 0 and 1 have extra priority from global structure
                    if (i == 1) {
                        extra = *(int*)(gChannelManager + 0x58);
                    } else {
                        extra = *(int*)(gChannelManager + 0x54);
                    }
                }
                uint32_t total = baseLoad + extra;
                // If any channel has total <= 7, set flag false
                if (total <= 7) {
                    allAboveThreshold = false;
                }
            }
        }

        // Second pass: find channel with smallest load < 8
        if (m_channelCount != 0) {
            for (uint32_t i = 0; i < m_channelCount; ++i) {
                uint32_t load = getChannelBaseLoad(i);
                if (!allAboveThreshold) {
                    // If not all channels are above threshold, include extra priority
                    int extra = 0;
                    if (i < 2) {
                        if (i == 1) {
                            extra = *(int*)(gChannelManager + 0x58);
                        } else {
                            extra = *(int*)(gChannelManager + 0x54);
                        }
                    }
                    load += extra;
                }
                // Update best if this load is smaller and less than 8
                if (load < bestValue && load < 8) {
                    bestIndex = i;
                    bestValue = load;
                }
            }
        }

        return bestIndex;
    }
};