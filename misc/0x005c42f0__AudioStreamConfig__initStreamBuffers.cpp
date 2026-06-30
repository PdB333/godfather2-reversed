// FUNC_NAME: AudioStreamConfig::initStreamBuffers
// Function address: 0x005c42f0
// Initializes stream buffer descriptors for EARS audio system.
// Each stream descriptor is 0x20 bytes, with fields for frame size, count, etc.
// Uses global arrays: g_streamCount (0xd=13 streams), g_streamConfigs (base at 0x01222070),
// and g_streamSourceSizes (table at 0x00e2b298).

#include <cstdint>

// Size of each stream configuration entry
const uint32_t STREAM_CONFIG_SIZE = 0x20;

// Stream configuration structure offsets (from base pointer)
// +0x00: unknown/padding
// +0x04: uint8_t enabledFlag (set to 1)
// +0x08: uint32_t frameSize (bytes per audio frame)
// +0x0c: uint32_t numFrames (calculated from buffer size and frame size)
// +0x10: uint32_t alignedSize (aligned to multiples of frameSize)
// +0x18: uint32_t bufferSize (fixed to 0x4000 = 16384 bytes)

// These are actually static globals but we'll declare as extern for clarity
extern uint32_t g_streamCount;           // DAT_01222068, set to 0xd
extern uint8_t* g_streamConfigs;         // DAT_0122206c, points to array of 13 entries
extern const uint32_t g_streamSourceSizes[]; // DAT_00e2b298, initial frame sizes for each stream

void __cdecl AudioStreamConfig::initStreamBuffers()
{
    int streamIndex = 0;
    g_streamCount = 0xd;                   // 13 streams
    g_streamConfigs = (uint8_t*)0x01222070; // base of stream config array

    int offset = 0;                        // offset within array (increments by 0x20)
    do {
        uint8_t* streamEntry = g_streamConfigs; // base pointer for this stream

        uint32_t sourceSize = g_streamSourceSizes[streamIndex]; // original frame size from table
        uint32_t frameSize = sourceSize;

        // Clamp to max 16 frames per packet? (if sourceSize > 15, use 16)
        if (sourceSize > 0xf) {
            frameSize = 0x10;
        }

        // Align sourceSize up to nearest multiple of frameSize
        uint32_t alignedSize = ((sourceSize - 1 + frameSize) / frameSize) * frameSize;

        // Ensure minimum aligned size of 4
        if ((int)alignedSize < 4) {
            alignedSize = 4;
        }

        // Set buffer size to 0x4000 (16384 bytes)
        *(uint32_t*)(streamEntry + offset + 0x18) = 0x4000;

        // Enable flag (byte)
        *(uint8_t*)(streamEntry + offset + 0x04) = 1;

        // Store frame size
        *(uint32_t*)(streamEntry + offset + 0x08) = frameSize;

        // Calculate number of frames: (bufferSize - headerOverhead) / alignedSize
        // headerOverhead = ((frameSize + 0x13) / frameSize) * frameSize (round up of 19 bytes? likely stream header)
        uint32_t headerOverhead = ((frameSize + 0x13) / frameSize) * frameSize;
        uint32_t numFrames = (0x4000 - headerOverhead) / alignedSize;
        *(uint32_t*)(streamEntry + offset + 0x0c) = numFrames;

        // Recalculate alignedSize if it was less than 4
        if ((int)alignedSize < 4) {
            alignedSize = 4;
        }

        // Store aligned size (rounded up to multiple of frameSize)
        *(uint32_t*)(streamEntry + offset + 0x10) = ((alignedSize - 1 + frameSize) / frameSize) * frameSize;

        streamIndex++;
        offset += STREAM_CONFIG_SIZE;
    } while (streamIndex < (int)g_streamCount); // loop until all streams configured
}