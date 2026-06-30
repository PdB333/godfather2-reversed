// FUNC_NAME: AudioStreamManager::handleStreamCommand
// Function address: 0x0060ca30
// Handles stream commands for the audio/streaming subsystem in the EARS engine.
// Uses global singleton at DAT_01205750 and state variables DAT_01205848/0120583c.

// External functions (EA engine internals)
void __cdecl enterCriticalSection(); // FUN_006102c0 - likely lock or sync
int __cdecl getCurrentStreamIndex(); // FUN_0060c9d0 - returns index/ID

// Global state pointers (assumed defined elsewhere)
extern class AudioStreamManager* g_streamManager; // DAT_01205750
extern int g_streamCurrentIndex; // DAT_01205848
extern int g_streamLastFlushedIndex; // DAT_0120583c

class AudioStreamManager {
public:
    // Vtable offsets (relative to object base):
    // +0x1A0: flushStream(int index) - flushes a stream slot by index
    void __thiscall flushStream(int streamIndex);
    
    // +0x148: writeStreamData(int type, void* data, int offset, int size, int unknown, uint bitShiftedSize)
    // Used for streaming data into a buffer
    void __thiscall writeStreamData(int type, void* data, int zero1, int size, int zero2, uint bitShiftedSize);
    
    // +0x144: sendCommand(int cmd, void* data, int extra)
    // Sends a command to the streamer
    void __thiscall sendCommand(int cmd, void* data, int extra);
};

void __thiscall AudioStreamManager::handleStreamCommand(int commandId, void* data, int size) {
    enterCriticalSection();
    
    AudioStreamManager* self = g_streamManager;
    
    if (commandId == 0x0D) { // 0x0D = STREAM_CMD_FLUSH_OR_PREPARE?
        if (size != 4) {
            // If stream index changed, flush the previous slot
            if (g_streamLastFlushedIndex != g_streamCurrentIndex) {
                self->flushStream(g_streamCurrentIndex);
                g_streamLastFlushedIndex = g_streamCurrentIndex;
            }
            // Write stream data with type=4, and a bit-shifted size for alignment
            self->writeStreamData(4, data, 0, size, 0, (uint)(size * 2) >> 2);
            return;
        }
        // When size==4, treat command as ID 6 (STREAM_CMD_OTHER)
        commandId = 6;
    }
    
    // General command dispatch
    int vtableBase = *(int*)self;
    int extra = getCurrentStreamIndex();
    self->sendCommand(commandId, data, extra);
}