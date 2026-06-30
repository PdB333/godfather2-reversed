// FUN_NAME: AudioStreamManager::updateStreams
// Function address: 0x005b3890
// Purpose: Updates all active audio streams in the manager.

struct AudioStreamNode; // forward declaration

class AudioStreamManager {
public:
    // +0x00: pointer to some internal data block
    // internalData +0x60: head of linked list of AudioStreamNode
    void updateStreams(); // __thiscall
};

// AudioStreamNode fields (offset in bytes from node base):
// +0x00: flags (low 16 bits: state, bit 15 used for active flag)
// +0x04: ?
// ...
// +0x50: streamId (offset 0x14 words = 0x50? wait: puVar3[0x15] is offset 0x15*4 = 0x54)
// Actually careful: puVar3 is uint*, so puVar3[0x15] is at offset 0x54 bytes.
// +0x34: some handle or pointer (puVar3[0xd])
// +0x60: next pointer (puVar3[0x18])
// Let's document:
// +0x00: uint32 flags
// +0x54: uint32 streamId (may be 0 if not used)
// +0x34: uint32 someHandle
// +0x60: AudioStreamNode* next

// External functions (likely in audio system):
extern bool isAudioCondition1(); // 0x005abd70
extern bool isAudioCondition2(int); // 0x0059c5c0
extern void stopAudio(); // 0x0059c3b0
extern bool isAudioPaused(); // 0x005a4140
extern int getAudioHandle(); // 0x005a3f20 - returns some base handle
extern AudioStreamNode* findAudioStream(int handle); // 0x005bb150 - returns node pointer
extern void destroyAudioStream(int handle); // 0x005bad80
extern void advanceStreamState(); // 0x005aa310 - moves to next stream state

void AudioStreamManager::updateStreams() {
    // Get head of stream list
    AudioStreamNode* pCurrent = *(AudioStreamNode**)(*(int*)(*(int*)this) + 0x60);
    // ^ Actually: *this is first field (maybe vtable?), then *(int*)(vtable + 0x60) is the list head?

    do {
        AudioStreamNode* pStream;
        do {
            pStream = pCurrent;
            if (pStream == nullptr) {
                return;
            }
            pCurrent = pStream->next; // offset 0x60
            // Skip nodes where bit 15 of flags is clear (inactive)
        } while ((~((unsigned char)(pStream->flags >> 0xF)) & 1) != 0); // bit 15 active flag

        uint32 streamId = pStream->streamId; // offset 0x54
        if (streamId != 0) {
            bool cond1 = isAudioCondition1(); // maybe isStreamPlaying()
            int handle;
            if (!cond1) {
                bool cond2 = isAudioCondition2(0); // maybe isStreamValid()
                if (cond2) {
                    stopAudio(); // stop the stream?
                    if (!isAudioPaused()) {
                        stopAudio(); // stop again if not paused
                        handle = getAudioHandle(); // get handle
                        handle = *(int*)(handle + 0xC); // offset 0xC from handle base
                    } else {
                        handle = 0;
                    }
                } else {
                    handle = 0;
                }
            } else {
                handle = streamId + 4; // handle derived from streamId
            }
            // If node has a handle at offset 0x34 and matches current node
            if (pStream->someHandle != 0) { // offset 0xd -> 0x34
                AudioStreamNode* foundNode = findAudioStream(handle);
                if (foundNode == pStream) {
                    destroyAudioStream(handle); // cleanup this stream
                }
            }
        }
        advanceStreamState(); // move to next state? maybe update internal counter
    } while (true);
}