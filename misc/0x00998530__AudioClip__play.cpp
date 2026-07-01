// FUNC_NAME: AudioClip::play

// Reconstructed C++ for function at 0x00998530
// This is AudioClip::play – starts or switches the audio clip playback

#pragma pack(push, 1)
struct AudioDataRefCounted
{
    void (__thiscall *vftable)(int); // +0x00: virtual destructor or finalizer
    short refCount;                   // +0x04: reference count
    short usedCount;                  // +0x06: usage count (e.g., number of active instances)
};
#pragma pack(pop)

class AudioClip
{
public:
    // fields (guessed offsets)
    void *streamBuffer;                     // +0x00
    // ... other fields ...
    void *ownerOrStreamManager;             // +0x0c
    uint8_t pad_0x10[0x10];                // +0x10 placeholder for stream buffer area
    void *currentSoundInstance;             // +0x1c: pointer to currently playing sound instance
    AudioDataRefCounted *currentAudioData;  // +0x20: currently assigned audio data (ref counted)
    uint32_t flags;                         // +0x4c: bitmask of state flags
    // ... more fields ...
};

// External functions (declarations)
void __thiscall AudioClip::stopSoundInstance(void *soundInstance);
void __thiscall AudioClip::setupStream(void *streamArea, int size);
void __thiscall AudioClip::startStream(void *streamManager);

void __thiscall AudioClip::play(AudioDataRefCounted *newAudioData)
{
    // If the clip is already in a "stopped/not playing" state (bit 2 cleared), proceed
    if ((this->flags & 0x4) == 0)
    {
        // Stop any existing sound instance
        if (this->currentSoundInstance != nullptr)
        {
            this->stopSoundInstance(this->currentSoundInstance);
        }

        // If there is a current audio data, release it (decrement usage count and possibly finalize)
        if ((this->flags & 0x20) != 0 && this->currentAudioData != nullptr)
        {
            AudioDataRefCounted *oldData = this->currentAudioData;
            if (oldData->refCount != 0)
            {
                oldData->usedCount--;
                if (oldData->usedCount == 0)
                {
                    // Call the virtual destructor/finalizer with argument 1 (maybe "release" flag)
                    oldData->vftable(1);
                }
            }
            this->currentAudioData = nullptr;
        }

        // Assign new audio data and increment its usage count
        this->currentAudioData = newAudioData;
        if (newAudioData->refCount != 0)
        {
            newAudioData->usedCount++;
        }

        // Set flag indicating audio data is loaded/active
        this->flags |= 0x20;

        // If the stream buffer is not yet initialized, set it up
        if ((this->flags & 0x40) == 0)
        {
            if (this->ownerOrStreamManager != nullptr)
            {
                this->startStream(this->ownerOrStreamManager);
            }
            this->setupStream(&this->streamBuffer, 0x8000); // allocate buffer of size 32KB
            this->flags |= 0x40;
        }
    }
    // If bit 2 is set (clip is locked/invalid state), do nothing
}