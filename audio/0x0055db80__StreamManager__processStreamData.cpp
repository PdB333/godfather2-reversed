// FUNC_NAME: StreamManager::processStreamData
// Address: 0x0055db80
// This function processes audio stream data and checks a state flag.
// It is called from two locations (0x00544ef0 and 0x00544f80), likely from
// an audio/stream update loop. The 'this' pointer is passed in ESI.

void __thiscall StreamManager::processStreamData(int streamId)
{
    // 60-byte buffer for stream data (e.g., formatted stream info)
    char streamBuffer[60];
    // 16-byte buffer for additional processing (e.g., sound resource handle)
    char resourceBuffer[16];

    // Initialize stream buffer from external data (e.g., fetch stream by ID)
    FUN_004b59d0(streamId, streamBuffer); // likely: getStreamData(streamId, streamBuffer)

    // Process the stream data (e.g., decode, prepare for playback)
    FUN_00aa3930(streamBuffer); // likely: processStream(streamBuffer)

    // Check a state flag in the associated audio object.
    // thisObj + 0x18 is a pointer to an AudioState or similar object.
    // +0xd8 is a byte flag (e.g., playback state). 0x07 = 7 = playing.
    if (*(char *)(*(int *)(this + 0x18) + 0xd8) == 7) {
        // Possibly log or trigger a debug/UI message.
        // Arguments: (1, 1, 0) might indicate a message type or priority.
        FUN_009f4240(1, 1, 0); // likely: debugPrint(priority, category, ...)
    }

    // Finalize processing or update resource handles.
    FUN_009f4c70(resourceBuffer); // likely: finalizeResource(resourceBuffer)
}