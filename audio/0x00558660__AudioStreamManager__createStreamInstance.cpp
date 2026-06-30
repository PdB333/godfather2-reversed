// FUNC_NAME: AudioStreamManager::createStreamInstance

void AudioStreamManager::createStreamInstance(uint *eventHandlePtr, uint soundId, AudioSpatialData *spatialData)
{
    byte localBuffer[176]; // stack buffer for audio context initialization
    uint eventHandle;
    AudioStreamData *streamData;
    AudioInstance *audioInstance;

    // Initialize audio system or context
    audioSystemInit();
    audioLocalContextInit(localBuffer);

    // Set context flags: offset 0x1d = 2, offset 0x20 = 6 (likely bitmask or type fields)
    localBuffer[0x1d] = 2;
    localBuffer[0x20] = 6;

    // Ensure TLS pointer is loaded (unused return value)
    TlsGetValue(gTlsIndex);

    // Allocate stream data block (0x200 bytes) with tag 0x2d
    streamData = (AudioStreamData *)memoryAlloc(0x200, 0x2d);
    streamData->size = 0x200; // +0x04

    // Finalize local context and get a pointer to the allocated block?
    // Note: the original code reassigns 'iVar2' to the return of FUN_009f4640, so we store it differently
    streamData = (AudioStreamData *)audioLocalContextFinalize(localBuffer); // +0x20 used?

    // Get the global audio instance (thread-local or singleton)
    audioInstance = getAudioInstance();
    if (audioInstance != nullptr)
    {
        // Zero out a portion of the audio instance structure
        audioInstance->field_0x48 = 0;
        audioInstance->field_0x4c = 0;
        audioInstance->field_0x50 = 0;
        audioInstance->field_0x54 = 0;
        audioInstance->field_0x58 = 0;
        audioInstance->field_0x5c = 0;
        audioInstance->field_0x40 = 0;
        audioInstance->field_0x44 = 0;
        audioInstance->field_0x60 = 0;
        audioInstance->field_0x64 = 0;
        audioInstance->field_0x68 = 0;
    }

    // Dereference event handle pointer
    eventHandle = *eventHandlePtr;

    // Register event with sound system
    audioRegisterEvent(soundId, eventHandle, 1);

    // Store encoded pointer to audio instance in stream data header
    streamData->instancePointer = (uint)(audioInstance >> 2) | 0xC0000000; // +0x2c

    // Flush audio system
    audioSystemFlush();

    // Send message 0x2001 with event handle
    sendAudioMessage(0x2001, eventHandle, 0);

    // Copy spatial data into audio instance
    // Note: spatialData layout: 8 bytes at offset 0, 8 bytes at offset 8, 4 bytes at offset 16
    audioInstance->spatialData.part0 = *((uint64 *)spatialData);          // +0x4c
    audioInstance->spatialData.part1 = *((uint64 *)spatialData + 1);      // +0x54
    audioInstance->spatialData.part2 = *((uint32 *)((char *)spatialData + 16)); // +0x5c

    // Send completion message with event handle pointer
    sendAudioMessage(0x2002, (uint)eventHandlePtr, 0);

    // Cleanup audio stream context
    audioStreamCleanup();
}