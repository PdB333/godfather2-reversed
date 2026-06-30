// FUNC_NAME: SoundPlayer::play
// Address: 0x00707c30
// Role: Begin or resume playback of a sound stream associated with this player object.

class SoundPlayer {
public:
    // Offsets relative to this (byte offsets):
    // +0x6C: int32 mStreamHandle       (handle to active stream, 0 = none)
    // +0x6D: uint8  mStreamRequested   (flag: stream play was requested)
    // +0x74: uint32 mFlags             (bit 13 (0x2000) = stream is playing flag)

    void play() {
        int32_t* streamHandle = reinterpret_cast<int32_t*>(reinterpret_cast<char*>(this) + 0x6C);
        uint8_t* streamRequested = reinterpret_cast<uint8_t*>(reinterpret_cast<char*>(this) + 0x6D);
        uint32_t* flags = reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(this) + 0x74);

        if (*streamHandle == 0) {
            if (*streamRequested == 0) {
                return;
            }

            AudioDataManager* mgr = GetAudioDataManager();   // FUN_0054a4d0
            if (mgr == nullptr) return;
            if (mgr->streamCount < 1) return;                // mgr + 0x0C
            if (mgr->streamArray[0] == nullptr) return;      // mgr + 0x08 -> array of pointers

            // Call virtual method (index 6) on the first stream object
            typedef int (*StreamVirtualMethod)(void*);
            StreamVirtualMethod getStream = reinterpret_cast<StreamVirtualMethod>(
                *reinterpret_cast<int*>(mgr->streamArray[0]) + 0x18);
            *streamHandle = getStream(mgr->streamArray[0]);

            AudioDataManager::PostEvent(0x2001, this, 0);    // FUN_009f01f0
            AudioDataManager::UpdateState();                  // FUN_0043b490
        }

        // Call virtual method at vtable offset 400 (0x190) on this object
        typedef void (*UpdateMethod)(SoundPlayer*);
        UpdateMethod update = reinterpret_cast<UpdateMethod>(
            *reinterpret_cast<int*>(this) + 400);
        update(this);

        if ((*flags & 0x2000) == 0) {
            *flags |= 0x2000;
            StreamManager::Resume(*streamHandle, 1);         // FUN_009e6ff0
        }
    }

private:
    // Dependencies (extern functions representing known system calls)
    AudioDataManager* GetAudioDataManager();                 // FUN_0054a4d0
};