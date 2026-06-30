// FUNC_NAME: StreamManager::updateTimeSlice
// Address: 0x0059e710
// This function processes a time slice for the audio stream manager, 
// advancing streams, sound banks, and pending callbacks until the given 
// time is exhausted or a pause flag is set.

#include <cstdint>

// Forward declarations of internal functions
static bool isStreamManagerActive();
static StreamManager* getStreamManager();
static void processStreams(uint32_t delta);
static void processSoundBankUpdates();
static void processNotifications();
static void processPendingCallback();
static void finalizeFrame();

// Global data (guessed offsets and pointers)
// gStreamManager is the singleton StreamManager pointer
static StreamManager* gStreamManager = reinterpret_cast<StreamManager*>(0x0119a9cc);
// gTotalStreamTime accumulates processed time
static uint32_t gTotalStreamTime = 0;
// gPauseFlag: if non-zero, processing stops
static uint32_t gPauseFlag = 0;

// StreamManager structure offsets (partial)
// +0x00: vtable? (not used)
// +0x08: pointer to QuantumInfo structure
// +0x24: remainingTime (uint32)
// QuantumInfo structure offsets:
// +0x24: quantumSize (uint32)

struct StreamManager {
    // +0x00: unknown (vtable?)
    // +0x08:
    void* quantumInfo;  // pointer to QuantumInfo
    // +0x24:
    uint32_t remainingTime; // time left in current slice
};

struct QuantumInfo {
    // +0x24:
    uint32_t quantumSize;   // fixed time quantum per iteration
};

// The pending callback count is stored at gStreamManager + 0x301c
// (relative to the base address of StreamManager singleton data area)
// This offset may actually be from a different global base
static int32_t* pendingCallbackCount = reinterpret_cast<int32_t*>(0x0119a9cc + 0x301c);

// Main time slice processing function
// param_1: time in milliseconds to process (or microseconds, based on game)
uint32_t StreamManager::updateTimeSlice(uint32_t deltaTime)
{
    uint32_t consumedTime = 0;  // return value: 0 if not fully consumed, 1 if fully consumed
    uint32_t quantumSize;
    StreamManager* manager;
    QuantumInfo* quantum;
    int32_t callbackCount;

    if (!isStreamManagerActive()) {
        return 0;
    }

    manager = getStreamManager();
    // Add the remaining time from previous call to this delta
    deltaTime += manager->remainingTime;

    quantum = reinterpret_cast<QuantumInfo*>(manager->quantumInfo);
    quantumSize = quantum->quantumSize;

    // If we have enough time to process at least one quantum...
    if (quantumSize <= deltaTime) {
        consumedTime = 1;
        do {
            // Process one quantum
            processStreams(quantumSize);
            processSoundBankUpdates();
            processNotifications();

            // Process all pending callbacks (e.g., streaming events)
            callbackCount = *pendingCallbackCount;
            if (callbackCount > 0) {
                for (int32_t i = 0; i < callbackCount; ++i) {
                    processPendingCallback();
                }
            }
            *pendingCallbackCount = 0;

            finalizeFrame();

            deltaTime -= quantumSize;
            gTotalStreamTime += quantumSize;

            // Check if the system is still active
            if (!isStreamManagerActive()) {
                return 1; // fully consumed
            }

        } while (gPauseFlag == 0 && quantumSize <= deltaTime);
    }

    // Save remaining delta time for the next call
    if (isStreamManagerActive()) {
        manager->remainingTime = deltaTime;
    }

    return consumedTime;
}