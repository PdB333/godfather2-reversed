// FUNC_NAME: TrinitySequencer::startSequence
// Address: 0x00597370
// Role: Allocates and starts a new sequence slot, loading the binary if needed.
// Global data structures (symbols from Ghidra):
//   gSequencePool - array of 0x1d0-byte entries (first byte is 'inUse' flag)
//   gSequenceState0, gSequenceState1, gSequenceState2, gSequenceState3 - parallel arrays of 0x74-byte entries for slot state
//   gDebugOutput - vtable for debug messaging (offsets: 4=abort, 8=error, 0x0c=warning, 0x10=copy)
//   gUseWaitQueueFlag - if non-zero, sequences with wait opcode are deferred
//   gWaitQueue - array of 0x50-byte entries for queued sequences
//   gWaitQueueCount - number of entries in wait queue
//   gCurrentSequence - pointer to currently active sequence state (used to copy into slot)

#include <cstdint>

// Forward declarations for called functions
void* TrinitySequencer::loadSequenceBinary(uint32_t seqId);
void TrinitySequencer::storeCurrentSequenceState(void* slot);
void TrinitySequencer::markSequenceActive(void* slot);

// Global arrays (from Ghidra data symbols)
extern uint8_t gSequencePool[16][0x1d0];         // DAT_0119a9d0
extern uint32_t gSequenceState0[16 * 0x74/4];    // DAT_0119ab8c (per-slot data, offset +0)
extern uint32_t gSequenceState1[16 * 0x74/4];    // DAT_0119ab90 (+4)
extern uint32_t gSequenceState2[16 * 0x74/4];    // DAT_0119ab94 (+8)
extern uint32_t gSequenceState3[16 * 0x74/4];    // DAT_0119ab98 (+12)
extern DebugOutput* gDebugOutput;                 // DAT_01205590 (vtable pointer)
extern uint8_t gUseWaitQueueFlag;                 // DAT_012055a0
extern uint32_t gWaitQueueCount;                  // DAT_01205598
extern WaitQueueEntry gWaitQueue[8];              // DAT_01221480 (max 8 entries, each 0x50 bytes)
extern SequenceState* gCurrentSequence;           // DAT_012055a4 (pointer to active sequence)

struct SequenceData {
    uint32_t sequenceId;       // +0x44?
    void* binaryPointer;       // +0x48? (0 if not loaded)
    // ... other fields
};

void* TrinitySequencer::startSequence(SequenceData* seqData)
{
    // Step 1: Find a free slot in the pool (first byte of each 0x1d0 entry is 'inUse' flag)
    int32_t slotIdx = 0;
    uint32_t offset = 0;
    while ((gSequencePool[0][offset] & 1) != 0) {
        offset += 0x1d0;
        slotIdx++;
        if (offset > 0x1cff) {
            // All slots occupied -> trigger error abort
            gDebugOutput->vtbl->abort();
            return nullptr;
        }
    }

    // The pool base pointer (unused check)
    if (&gSequencePool[slotIdx] == nullptr) {
        gDebugOutput->vtbl->abort();
        return nullptr;
    }

    // Step 2: Load sequence binary if not already loaded
    void* seqBinary = seqData->binaryPointer;
    if (seqBinary == nullptr) {
        seqBinary = TrinitySequencer::loadSequenceBinary(seqData->sequenceId);
    }
    if (seqBinary == nullptr) {
        gDebugOutput->vtbl->warning(gDebugOutput, "TRINITY - Can't find seq binary %d", seqData->sequenceId);
    }

    // Step 3: Check if we should enqueue this sequence (wait opcode present)
    if (gUseWaitQueueFlag) {
        // Parse binary: binary+0xb8 points to an array of short opcodes
        int16_t* opcodes = *(int16_t**)((uint8_t*)seqBinary + 0xb8);
        int16_t currentOpcode = *opcodes;
        int16_t* cursor = opcodes;
        while (currentOpcode != 0x100) {  // end marker?
            if (currentOpcode == 0x300) { // wait opcode
                if (gWaitQueueCount > 7) {
                    gDebugOutput->vtbl->error(gDebugOutput,
                        "ERROR: TrinitySequencer::start : Too many queued sequences in wait queue");
                    return nullptr;
                }
                int32_t queueIdx = gWaitQueueCount * 0x50; // entry stride 0x50
                gWaitQueueCount++;
                gDebugOutput->vtbl->copy(&gWaitQueue[queueIdx], seqData, 0x50);
                // Clear bit 1? (presumably some flag)
                *((uint32_t*)&gWaitQueue[queueIdx] + 1) &= ~2; // & 0xfffffffd
                return nullptr;
            }
            if (*(opcodes + 1) == 0) break; // next offset zero?
            cursor = (int16_t*)((uint8_t*)cursor + (uint16_t)cursor[1]); // advance by offset in second short
            currentOpcode = *cursor;
        }
    }

    // Step 4: Start the sequence in the allocated slot
    gCurrentSequence->vtbl->method_10();  // some prepare/reset
    TrinitySequencer::storeCurrentSequenceState(&gSequenceState0[slotIdx * 0x74/4]);

    // Copy current sequence state into slot (four state arrays)
    gSequenceState0[slotIdx * 0x74/4] = gCurrentSequence[1];  // +0x04
    gSequenceState1[slotIdx * 0x74/4] = gCurrentSequence[4];  // +0x10
    gSequenceState2[slotIdx * 0x74/4] = gCurrentSequence[3];  // +0x0c
    gSequenceState3[slotIdx * 0x74/4] = gCurrentSequence[2];  // +0x08

    TrinitySequencer::markSequenceActive(&gSequencePool[slotIdx]);

    // Return pointer to the slot's base (the pool entry)
    return &gSequencePool[slotIdx];
}