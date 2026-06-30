// FUNC_NAME: SoundEventManager::popFromPriorityQueues
// Address: 0x00613570
// Role: Pops the top element from one or more priority queues (sound events) into global current buffers and triggers processing

#include <cstdint>

// Sound event structure (64 bytes)
struct SoundEvent {
    uint32_t data[16]; // +0x00 to +0x3C
};

// Global storage for current events being processed
static SoundEvent currentPrimaryEvent;    // 0x011f69b0
static SoundEvent currentSecondaryAEvent; // 0x011f69f0
static SoundEvent currentTertiaryEvent;   // 0x011f6a30
static SoundEvent currentSecondaryBEvent; // 0x011f6b30

// Queue counts and arrays
static int32_t primaryQueueCount;         // 0x011f6bf0
static SoundEvent primaryQueue[?];        // 0x011f6c00, each 0x40 bytes

static int32_t secondaryAQueueCount;      // 0x011f7010
static SoundEvent secondaryAQueue[?];     // 0x011f7020

static int32_t secondaryBQueueCount;      // 0x011f6e00
static SoundEvent secondaryBQueue[?];     // 0x011f6e10

static int32_t tertiaryQueueCount;        // 0x011f7220
static SoundEvent tertiaryQueue[?];       // 0x011f7230

static uint32_t processingFlags;          // 0x011f7430, bit 0 = processing enabled

// Forward declarations of processing functions
void processPrimaryEvent(void);
void processSecondaryEvent(void);

void SoundEventManager::popFromPriorityQueues(uint32_t priorityMask)
{
    // Bit 0 (1): pop from primary queue
    if ((priorityMask & 1) != 0 && 0 < primaryQueueCount) {
        primaryQueueCount--;
        currentPrimaryEvent = primaryQueue[primaryQueueCount]; // Pop LIFO
    }

    // Bit 1 (2): pop from secondary queues (A and B)
    if ((priorityMask & 2) != 0) {
        if (0 < secondaryAQueueCount) {
            secondaryAQueueCount--;
            currentSecondaryAEvent = secondaryAQueue[secondaryAQueueCount];
        }
        if (0 < secondaryBQueueCount) {
            secondaryBQueueCount--;
            currentSecondaryBEvent = secondaryBQueue[secondaryBQueueCount];
        }
    }

    // Bit 2 (4): pop from tertiary queue
    if ((priorityMask & 4) != 0 && 0 < tertiaryQueueCount) {
        tertiaryQueueCount--;
        currentTertiaryEvent = tertiaryQueue[tertiaryQueueCount];
    }

    // If processing is enabled, dispatch based on primary bit
    if ((processingFlags & 1) != 0) {
        if ((priorityMask & 1) == 1) {
            processPrimaryEvent(); // 0x00614a50
        } else {
            processSecondaryEvent(); // 0x00614910
        }
    }
}