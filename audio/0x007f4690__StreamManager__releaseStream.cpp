// FUNC_NAME: StreamManager::releaseStream
void __fastcall StreamManager::releaseStream(StreamManager* this)
{
    // +0x1c84: presumably a pointer to a stream object (e.g., BNKStream or MultiTrackStream)
    if (*(int*)((char*)this + 0x1c84) != 0) {
        // stop stream playback/release resources (0x0054e520)
        stopStream();
        // destroy/free the stream object (0x0054e2e0)
        destroyStream(*(void**)((char*)this + 0x1c84));
        // nullify the pointer to avoid dangling reference
        *(int*)((char*)this + 0x1c84) = 0;
    }
}