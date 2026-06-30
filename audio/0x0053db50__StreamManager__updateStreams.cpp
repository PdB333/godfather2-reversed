// FUNC_NAME: StreamManager::updateStreams
// Function address: 0x0053db50
// Role: Updates two streaming buffers (16 bytes each) from a provided data source.
// This is called per slot (indexed by g_slotIndex) to push audio/stream data to the audio engine.

// Global data (from Ghidra):
// g_slotIndex  (DAT_0121bf30) - Current slot/stream index.
// g_streamArrayA (DAT_01198e88) - Array of stream handles/slots (size 0x1B per entry), indexed by slot.
// g_streamArrayB (DAT_01198e8c) - Array of stream handles/slots (size 0x1B per entry), indexed by slot.
// g_audioEngineHandle (DAT_0121be9c) - Handle/pointer to the audio engine.

// Helper function: processStreamBuffer (FUN_0060add0)
extern void __cdecl processStreamBuffer(void* audioEngineHandle, void* streamHandle, void* bufferData);

// Static arrays (global variables)
extern int g_slotIndex;
extern char g_streamArrayA[]; // Base of array (each element 0x1B bytes)
extern char g_streamArrayB[]; // Base of array (each element 0x1B bytes)
extern void* g_audioEngineHandle;

void __thiscall StreamManager::updateStreams(void* streamData)
{
    // streamData is a pointer to 32 bytes (8 ints) containing two 16-byte buffers.
    int* data = (int*)streamData;
    int bufferA[4];
    int bufferB[4];

    // Calculate pointer to slot entry in array A, offset by slot index * 0x1B
    void* streamHandleA = *(void**)(g_streamArrayA + g_slotIndex * 0x1B);
    if (streamHandleA != nullptr) {
        bufferA[0] = data[0];
        bufferA[1] = data[1];
        bufferA[2] = data[2];
        bufferA[3] = data[3];
        processStreamBuffer(g_audioEngineHandle, streamHandleA, bufferA);
    }

    // Calculate pointer to slot entry in array B, offset by slot index * 0x1B
    void* streamHandleB = *(void**)(g_streamArrayB + g_slotIndex * 0x1B);
    if (streamHandleB != nullptr) {
        bufferB[0] = data[4];
        bufferB[1] = data[5];
        bufferB[2] = data[6];
        bufferB[3] = data[7];
        processStreamBuffer(g_audioEngineHandle, streamHandleB, bufferB);
    }
}