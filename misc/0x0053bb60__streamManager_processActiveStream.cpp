// FUNC_NAME: streamManager_processActiveStream
// Address: 0x0053bb60
// Role: Checks if the stream slot indexed by a global variable is active (non-zero first field), and if so calls a processing function.

#include <cstdint>

// Size of each stream slot: 0x3c bytes
#define STREAM_SLOT_SIZE 0x3c

// Base address of the stream slot array
#define STREAM_SLOT_ARRAY_BASE 0x011254c0

// Global index into the array (uint32)
#define STREAM_INDEX (*reinterpret_cast<uint32_t*>(0x01125389))

// Forward declaration of the processing function
void streamProcessFunction(); // corresponds to FUN_006063b0

void streamManager_processActiveStream()
{
    // Compute pointer to the stream slot
    uint8_t* slotPtr = reinterpret_cast<uint8_t*>(STREAM_SLOT_ARRAY_BASE) + STREAM_INDEX * STREAM_SLOT_SIZE;
    
    // First field is a 32-bit integer indicating activity (non-zero = active)
    int32_t isValid = *reinterpret_cast<int32_t*>(slotPtr);
    
    if (isValid != 0) {
        streamProcessFunction();
    }
}