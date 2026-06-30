// FUNC_NAME: StreamManager::stopStream
// Function address: 0x006e72d0
// Role: Stops a stream if it is active (flagged at +0x8a bit 4) and decrements the active stream count.

class StreamObject; // forward declaration

class StreamManager {
public:
    void __thiscall stopStream(StreamObject* stream);
    int activeStreamCount; // offset 0x2020: number of currently active streams
};

class StreamObject {
public:
    byte flags; // offset 0x8a: bit 4 = active
    void stop(); // FUN_006e7030: internal stream stop handler
};

void __thiscall StreamManager::stopStream(StreamObject* stream) {
    // Check if stream has active flag (bit 4)
    if ((stream->flags & 0x10) != 0) {
        // Stop the stream (calls internal closure)
        stream->stop();
        // Clear the active flag
        stream->flags &= ~0x10;
        // Decrement the manager's active stream count
        this->activeStreamCount--;
    }
}