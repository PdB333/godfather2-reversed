// FUNC_NAME: TrinitySequencer::start
// Address: 0x00597370
// This function starts a Trinity sequence. It finds a free slot in the sequence pool,
// loads the sequence binary if needed, checks for wait commands (0x300) to queue the sequence,
// and initializes the slot with current global state.

#include <cstdint>

// Forward declarations of global data and helper functions
extern uint8_t gSequencePoolFlags[0x1d0 * 16]; // DAT_0119a9d0, stride 0x1d0, flag byte at offset 0
extern uint32_t gSequenceState1[16]; // DAT_0119ab8c, stride 0x74
extern uint32_t gSequenceState2[16]; // DAT_0119ab90, stride 0x74
extern uint32_t gSequenceState3[16]; // DAT_0119ab94, stride 0x74
extern uint32_t gSequenceState4[16]; // DAT_0119ab98, stride 0x74

extern void* gErrorHandler; // DAT_01205590, vtable-like pointer
extern uint8_t gCheckWaitCommands; // DAT_012055a0
extern int32_t gQueuedSequenceCount; // DAT_01205598
extern uint8_t gSequenceQueue[0x50 * 8]; // DAT_01221480, queue of size 0x50 per entry
extern uint32_t gSequenceQueueFlags[8]; // DAT_01221470, flags for queue entries
extern void* gCurrentSequenceContext; // DAT_012055a4, pointer to some global state

// Helper functions
int32_t findSequenceBinary(int32_t sequenceId); // FUN_00597000
void sequenceStartHelper1(); // FUN_005992a0
void sequenceStartHelper2(); // FUN_00599340

// Error logging function pointers (offsets from gErrorHandler)
typedef void (*ErrorLogFunc)(void* handler, const char* msg, ...);
typedef void (*ErrorLogFuncInt)(void* handler, const char* msg, int32_t value);
typedef void (*MemCopyFunc)(void* dest, void* src, int32_t size);

void* TrinitySequencer::start(void* seqDef) {
    int32_t slotIndex = 0;
    uint32_t offset = 0;

    // Find a free slot in the sequence pool (flag byte at offset 0, stride 0x1d0)
    while ((gSequencePoolFlags[offset] & 1) != 0) {
        offset += 0x1d0;
        slotIndex++;
        if (offset > 0x1cff) {
            // No free slot, call error handler
            ((ErrorLogFunc)(*(void**)gErrorHandler + 4))(gErrorHandler, "No free sequence slot");
            return nullptr;
        }
    }

    // Check if the computed slot pointer is valid (decompiler artifact, always true)
    if (&gSequencePoolFlags[slotIndex * 0x74] == nullptr) {
        ((ErrorLogFunc)(*(void**)gErrorHandler + 4))(gErrorHandler, "Invalid slot pointer");
        return nullptr;
    }

    // Get sequence binary pointer from seqDef (+0x48)
    int32_t seqBinary = *(int32_t*)((uint8_t*)seqDef + 0x48);
    if (seqBinary == 0) {
        seqBinary = findSequenceBinary(*(int32_t*)((uint8_t*)seqDef + 0x44));
    }
    if (seqBinary == 0) {
        ((ErrorLogFuncInt)(*(void**)gErrorHandler + 0xc))(gErrorHandler, "TRINITY - Can't find seq binary %d", *(int32_t*)((uint8_t*)seqDef + 0x44));
    }

    // If global flag is set, check for wait commands (0x300) in the sequence binary
    if (gCheckWaitCommands != 0) {
        int16_t* cmdPtr = *(int16_t**)(seqBinary + 0xb8);
        int16_t cmd = *cmdPtr;
        int16_t* currentCmd = cmdPtr;
        while (cmd != 0x100) {
            if (cmd == 0x300) {
                if (gQueuedSequenceCount > 7) {
                    ((ErrorLogFunc)(*(void**)gErrorHandler + 8))(gErrorHandler, "ERROR: TrinitySequencer::start : Too many queued sequences in wait queue");
                    return nullptr;
                }
                // Queue the sequence definition (size 0x50)
                int32_t queueIndex = gQueuedSequenceCount * 0x50;
                gQueuedSequenceCount++;
                ((MemCopyFunc)(*(void**)gErrorHandler + 0x10))(&gSequenceQueue[queueIndex], seqDef, 0x50);
                // Clear bit 1 in the queue flags
                gSequenceQueueFlags[gQueuedSequenceCount * 0x50] &= ~2;
                return nullptr;
            }
            if (currentCmd[1] == 0) break;
            // Advance to next command using the offset stored in the second short
            currentCmd = (int16_t*)((uint8_t*)currentCmd + (uint16_t)currentCmd[1]);
            cmd = *currentCmd;
        }
    }

    // No wait command found, proceed to start the sequence
    ((void (*)())(*(void**)gCurrentSequenceContext + 0x10))();
    sequenceStartHelper1();
    sequenceStartHelper2();

    // Copy global state into the slot's state arrays (stride 0x74)
    int32_t* contextPtr = (int32_t*)gCurrentSequenceContext;
    gSequenceState1[slotIndex * 0x74] = contextPtr[1];
    gSequenceState2[slotIndex * 0x74] = contextPtr[4];
    gSequenceState3[slotIndex * 0x74] = contextPtr[3];
    gSequenceState4[slotIndex * 0x74] = contextPtr[2];

    // Return pointer to the slot (base + slotIndex * 0x74)
    return &gSequencePoolFlags[slotIndex * 0x74];
}