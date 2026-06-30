// FUNC_NAME: SampleBuffer::advanceSample
// Address: 0x0065ca60
// Role: Advances a triple-buffered sample history, rotating newest->recent->oldest and processing the displaced oldest pair.

#include <cstdint>

// Global flag and buffer used by the function
static bool g_sampleInitFlag = false;   // DAT_0120588f
static uint32_t g_globalSampleBuffer[2]; // DAT_01203740 (size 8 bytes)

// Forward declarations of helper functions called within
void processOldestSample(uint32_t sampleValue);   // FUN_0065c810
void initSampleSystem();                         // combines FUN_00662100 and FUN_006622a0
void copyToGlobalBuffer(uint32_t* source);       // FUN_00662350 (copies 8 bytes)

// Struct representing the sample buffer's internal state
// Offsets are relative to 'this' pointer
class SampleBuffer {
public:
    // Offset +0x00: (unused? or padding)
    // Offset +0x04:
    uint32_t m_lastUpdateTimestamp;   // Last time the buffer was advanced
    // Offset +0x08:
    uint32_t m_firstTimestampSet;     // Non-zero when first timestamp has been stored

    // Triple buffer: each pair is two uint32_t values (8 bytes).
    // The indices are arranged as:
    //   newest[2]   at offsets 0x0C, 0x10
    //   recent[2]   at offsets 0x14, 0x18
    //   oldest[2]   at offsets 0x1C, 0x20

    uint32_t m_newest[2];   // +0x0C
    uint32_t m_recent[2];   // +0x14
    uint32_t m_oldest[2];   // +0x1C

    void advance(uint32_t timestamp) {
        // If first timestamp not set, initialize it
        if (m_firstTimestampSet == 0) {
            m_firstTimestampSet = timestamp;
        }

        // Only advance if at least 30000 ms (30 sec) have elapsed since last advance
        if (timestamp - m_lastUpdateTimestamp <= 30000) {
            return;
        }

        m_lastUpdateTimestamp = timestamp;

        // Perform the triple buffer rotation:
        // 1. Swap the two values in the oldest pair
        uint32_t temp = m_oldest[1];
        m_oldest[1] = m_oldest[0];
        m_oldest[0] = temp;

        // 2. Shift newest pair to recent pair
        m_recent[0] = m_newest[0];
        m_recent[1] = m_newest[1];

        // 3. The former first element of oldest (now swapped to element 1) is processed
        processOldestSample(m_oldest[1]);

        // 4. Initialize the global system once
        if (!g_sampleInitFlag) {
            g_sampleInitFlag = true;
            initSampleSystem();
        }

        // 5. Copy the newest pair (which now contains the newly arrived sample) to the global buffer
        //    Note: newest pair is at offsets +0x0C; copy 8 bytes (2 uint32)
        copyToGlobalBuffer(m_newest);
    }
};
// End of reconstructed function