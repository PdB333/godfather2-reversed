// FUNC_NAME: BNKStreamManager::updateStreamState
#include <cstdint>

// Forward declarations (actual types from game binary)
class BNKStreamManager;
class StreamContext;

// Global stream manager singleton (loaded from DAT_01223510)
extern BNKStreamManager* g_streamManager;

// Mock virtual table for BNKStreamManager (offsets relative to vtable pointer)
// Offsets used:
// 0x48: bool isReady(uint32_t handle)
// 0x4c: int32_t loadStream(uint32_t handle, const char* name, uint32_t param3, uint32_t param4)
// 0x8c: bool isLoadComplete(uint32_t taskId)

// Default string used when no name provided
extern const char* DEFAULT_STREAM_NAME; // DAT_0120546e (likely empty string)

// Internal structure allocated per stream request (at this+0x1b4)
struct StreamState {
    // +0x00 to +0x1C: unknown
    // +0x20: const char* name1 (used in state 0/1)
    // +0x24: uint32_t flag? (enables state 0)
    // +0x30: const char* name2 (used in state 1 retry)
    // +0x34: uint32_t flag? (enables state 1)
    // +0x40: const char* name3 (used in state 2)
    // +0x44: uint32_t flag? (enables state 2)
    // +0x50: int32_t maxRetries (0 means infinite? -1 means set to -1)
    // +0x60: int32_t state (0=init,1=retry,2=finalize,3=done)
    // +0x64: int32_t retryCountdown (initialized from +0x50)
    // +0x68: uint8_t activeFlag (set to 0 on failure)
    uint32_t unk00;
    uint32_t unk04;
    uint32_t unk08;
    uint32_t unk0C;
    uint32_t unk10;
    uint32_t unk14;
    uint32_t unk18;
    uint32_t unk1C;
    const char* name1;   // +0x20
    uint32_t flag24;     // +0x24
    uint32_t unk28;
    uint32_t unk2C;
    const char* name2;   // +0x30
    uint32_t flag34;     // +0x34
    uint32_t unk38;
    uint32_t unk3C;
    const char* name3;   // +0x40
    uint32_t flag44;     // +0x44
    uint32_t unk48;
    uint32_t unk4C;
    int32_t maxRetries;  // +0x50
    uint32_t unk54;
    uint32_t unk58;
    uint32_t unk5C;
    int32_t state;       // +0x60
    int32_t retryCount;  // +0x64
    uint8_t activeFlag;  // +0x68
};

// This class (this at ESI) is the stream request owner
class BNKStreamRequest {
public:
    StreamState* pStreamState; // +0x1b4
    uint32_t handle;           // +0x1c8 (passed to manager)
    int32_t currentTaskId;     // +0x1cc (set negative initially)
    int32_t lastTaskId;        // +0x1d0
    uint32_t param20C;         // +0x20c (opaque)
    uint32_t param248;         // +0x248 (opaque)

    // Returns true when state becomes 3 (done)
    // On failure, sets pStreamState->activeFlag = 0 and returns false.
    bool updateStreamState() {
        bool bFailure = false;
        do {
            // Inner loop processes state transitions
            while (true) {
                StreamState* state = pStreamState;
                int32_t st = state->state;

                // State 0: Initial loading attempt
                if (st == 0) {
                    break; // Go to state 0 handler below
                }

                // State 1: Retry loop with countdown
                if (st == 1) {
                    // Check preconditions (required data and active flag)
                    if (state->flag34 == 0 || state->retryCount == 0 || state->activeFlag == 0) {
                        state->state = 2;
                        goto LAB_005e919f;
                    }

                    // Check if previous task completed or stream not ready
                    bool loadDone = g_streamManager->isLoadComplete(lastTaskId);
                    bool streamReady = g_streamManager->isReady(handle);
                    if (!loadDone || !streamReady) {
                        goto LAB_005e919f;
                    }

                    // Perform retry load with name2
                    const char* name = state->name2 ? state->name2 : DEFAULT_STREAM_NAME;
                    int32_t taskId = g_streamManager->loadStream(handle, name, param20C, param248);
                    lastTaskId = taskId;

                    if (taskId < 0) {
                        // Load failed: mark inactive
                        state->activeFlag = 0;
                    } else if (currentTaskId < 0) {
                        // First successful task: store as current
                        currentTaskId = taskId;
                    }

                    // Decrement retry counter
                    if (state->retryCount > 0) {
                        state->retryCount--;
                        if (state->retryCount == 0) {
                            state->state = 2;
                        }
                    }
                    goto LAB_005e919f;
                }

                // State 2: Finalize (attempt load with name3 if available)
                if (st == 2) {
                    // Check if optional third load exists
                    if (state->flag44 != 0 && state->activeFlag != 0) {
                        if (g_streamManager->isReady(handle)) {
                            const char* name = state->name3 ? state->name3 : DEFAULT_STREAM_NAME;
                            int32_t taskId = g_streamManager->loadStream(handle, name, param20C, param248);
                            lastTaskId = taskId;

                            if (taskId < 0) {
                                state->activeFlag = 0;
                            } else if (currentTaskId < 0) {
                                currentTaskId = taskId;
                                // If this is the first task, move to state 3 (done)
                                state->state = 3;
                                goto LAB_005e919f;
                            }
                        }
                    }
                    state->state = 3;
                    goto LAB_005e919f;
                }

                // If we reach here, state is out of expected range (should not happen)
                goto LAB_005e919f;
            }

            // Handle state 0 after breaking from loop
            // Only process if precondition (data at +0x24) and flag68 are valid
            StreamState* state = pStreamState;
            if (state->flag24 != 0 && state->activeFlag != 0) {
                if (g_streamManager->isReady(handle)) {
                    const char* name = state->name1 ? state->name1 : DEFAULT_STREAM_NAME;
                    int32_t taskId = g_streamManager->loadStream(handle, name, param20C, param248);
                    lastTaskId = taskId;

                    if (taskId < 0) {
                        // Load failed: set failure flag and mark inactive
                        bFailure = true;
                        state->activeFlag = 0;
                    } else if (currentTaskId < 0) {
                        // First load: store task ID
                        currentTaskId = taskId;
                    }
                }
            }

            // Transition to state 1 (retry loop)
            state->state = 1;
            // Initialize retry counter: if maxRetries is 0, set to -1 (infinite?),
            // otherwise use the value
            if (state->maxRetries == 0) {
                state->retryCount = -1;
            } else {
                state->retryCount = state->maxRetries;
            }
        } while (!bFailure);

    LAB_005e919f:
        // Return true if state reached 3 (completed)
        return (pStreamState->state == 3);
    }
};