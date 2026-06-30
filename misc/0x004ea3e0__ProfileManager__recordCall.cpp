// FUNC_NAME: ProfileManager::recordCall
#include <cstdint>
#include <intrin.h> // for __readfsdword

// Profiler context data (size 0x98 = 152 bytes)
struct ProfilerContext {
    int32_t m_active;      // +0x00 – first context's first dword acts as global enable flag
    int32_t m_clearFlag;   // +0x04 – reset each frame
    int32_t padding[36];   // fills to total 0x98
};

// Profile buffer structure: write pointer at offset 0x14
struct ProfileBuffer {
    uint8_t unknown[0x14]; // +0x00..+0x13
    int32_t* writePtr;     // +0x14
};

// Global profile buffers (from DAT_01206880 and DAT_012068e8)
extern ProfileBuffer g_profileBuffer0;
extern ProfileBuffer g_profileBuffer1;

// Symbol address written into the log (PTR_LAB_01124be4)
extern void* s_logLabel;

class ProfileManager {
public:
    // Two contexts, offset +0x00 and +0x98
    ProfilerContext m_contexts[2];

    // @param forceFlag  Forces logging when == 2
    void recordCall(int forceFlag) {
        // Fetch frame/state indicator from thread-local storage
        // (Windows TEB, offset 0x2C -> pointer to some data -> +0x34)
        uint32_t tebBase = __readfsdword(0x2C);
        int* pTlsData = *(int**)(tebBase);
        int frameState = *(int*)(pTlsData + 0x34);

        // Clear the second dword in the context corresponding to the current frame
        if ((frameState != 1) || (m_contexts[0].m_active == 0) || (forceFlag == 2)) {
            int contextIndex = (frameState != 0) ? 1 : 0;
            m_contexts[contextIndex].m_clearFlag = 0;
        }

        // Write profile log entry if (active and frameState==1) or forced
        if (((frameState == 1) && (m_contexts[0].m_active != 0)) || (forceFlag == 2)) {
            // Select buffer: frameState != 0 -> use the second buffer
            ProfileBuffer* buf = (frameState != 0) ? &g_profileBuffer1 : &g_profileBuffer0;

            // Push a record: symbol address + frame indicator
            *(void**)(buf->writePtr) = s_logLabel;
            buf->writePtr += 1;          // advance 4 bytes
            *((int32_t*)(buf->writePtr)) = (frameState != 0) ? 1 : 0;
            buf->writePtr += 1;          // advance 4 bytes
        }
    }
};