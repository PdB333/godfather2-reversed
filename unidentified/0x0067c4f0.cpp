// FUN_NAME: AudioManager::shutdownWithRetry

// Address: 0x0067c4f0
// Purpose: Shuts down audio subsystem with a retry loop (max 5 attempts) until audio is no longer busy.
// Uses a temporary stack struct initialized from global audio state pointer (DAT_01206940).

#include <cstdint>

// Forward declarations of internal audio functions (likely members of AudioManager)
extern void AudioManager::enterCriticalSection();   // FUN_004034c0
extern bool AudioManager::isAudioBusy();           // FUN_004035a0 (returns non-zero if busy)
extern void AudioManager::resetAudioState(void* state, int32_t flag); // FUN_00408a00
extern void AudioManager::stopAudioStream(int32_t streamId); // FUN_0068bcd0
extern void AudioManager::releaseAudioData(int32_t dataId); // FUN_0068baf0
extern void AudioManager::leaveCriticalSection();  // FUN_00403530

// Global audio state pointer (from DAT_01206940)
extern void* g_pAudioState;

// Temporary struct used to pass audio state + flags to resetAudioState
#pragma pack(push, 1)
struct AudioStateTemp {
    void* pState;   // +0x00: pointer to global audio state (g_pAudioState)
    int32_t flags;  // +0x04: set to 0
    int8_t extra;   // +0x08: set to 0 (alignment/extra byte)
};
#pragma pack(pop)

void AudioManager::shutdownWithRetry()
{
    // Enter critical section to protect shared audio state
    AudioManager::enterCriticalSection();

    int32_t retryCount = 5;

    while (true)
    {
        bool bBusy = AudioManager::isAudioBusy();
        int32_t nextRetry = retryCount;

        if (bBusy)
        {
            nextRetry = retryCount - 1;
            if (retryCount == 0)   // retries exhausted, exit loop
                break;
        }

        // Build temporary state struct on stack
        AudioStateTemp temp;
        temp.pState = g_pAudioState;
        temp.flags  = 0;
        temp.extra  = 0;

        // Reset audio state using this temporary structure
        AudioManager::resetAudioState(&temp, 0);

        // Stop default audio stream (0)
        AudioManager::stopAudioStream(0);
        // Release all audio data (0 = default)
        AudioManager::releaseAudioData(0);

        retryCount = nextRetry;
    }

    AudioManager::leaveCriticalSection();
}