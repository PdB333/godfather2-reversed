// FUNC_NAME: AudioStreamPlayer::advancePendingSound

// Global queue handle and counter for pending audio data
static int g_pendingQueueHandle = 0; // DAT_012069c4
static int g_pendingQueueCounter = 0; // _DAT_012069c8

// External helper functions (provided by the engine)
void* dequeueFromAudioQueue(void); // FUN_00407da0
void destroyAudioQueue(int* queueHandle, int size); // FUN_004084d0

// Reconstructed struct for the object (offsets known from disassembly)
struct AudioStreamPlayer {
    // ... other fields ...
    int  activeBuffer;   // +0x20 (nullptr when no active buffer)
    byte stateFlags;     // +0x28 (bit0: ?, bit1: pending data flag, bit3: processed flag)
    // ... other fields ...
};

void AudioStreamPlayer::advancePendingSound(void) {
    // Only proceed if we are not in a "pending + no active buffer" state
    if (((stateFlags & 2) == 0) || (activeBuffer != 0)) {
        if (g_pendingQueueHandle != 0) {
            g_pendingQueueCounter++;  // increment usage counter

            void* buffer = dequeueFromAudioQueue(); // get next pending buffer
            if (buffer != nullptr) {
                // Increment sequence number on the buffer (15‑bit counter modulo 0x8000)
                uint16_t seq = *(uint16_t*)((uint8_t*)buffer + 0x14);
                seq = (((seq + 1) ^ seq) & 0x7FFF) ^ seq; // increment without overflow wrap
                *(uint16_t*)((uint8_t*)buffer + 0x14) = seq;

                stateFlags |= 8; // mark that processing has been attempted
                return;
            }

            // No buffer available – release the queue
            destroyAudioQueue(&g_pendingQueueHandle, 0x1000);
        }

        stateFlags |= 8; // mark done
    }
}