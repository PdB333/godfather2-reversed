// FUNC_NAME: AudioDataManager::~AudioDataManager

class AudioDataManager {
public:
    ~AudioDataManager();
private:
    // Offsets (in bytes):
    // +0x000: vtable pointer (set to PTR_FUN_00d754b0)
    // +0x0BC: secondary vtable pointer (set to PTR_FUN_00d75498)
    // +0x10C: pointer to a child object (m_childPtr)
    // +0x170: array of 3 child pointers (m_childArray[3])
};

extern void* PTR_FUN_00d754b0;
extern void* PTR_FUN_00d75498;
extern int DAT_0120e93c;

void AudioDataManager::~AudioDataManager() {
    // Set vtables to base class vtables (destruction order)
    *(void**)this = &PTR_FUN_00d754b0;
    *(void**)((char*)this + 0xBC) = &PTR_FUN_00d75498;

    // Call base destructor
    FUN_00858e40();

    // If child at offset 0x10C exists, release it
    if (*(void**)((char*)this + 0x10C) != nullptr) {
        FUN_004df600();
    }

    // Unlock mutex
    FUN_004086d0(&DAT_0120e93c);

    // Clean up three child objects in reverse order (offsets 0x190, 0x180, 0x170)
    for (int i = 2; i >= 0; i--) {
        void** ptr = (void**)((char*)this + 0x170 + i * 4);
        if (*ptr != nullptr) {
            // Clear reference count or similar at offset 8 of the child object
            *(int*)(*ptr + 8) = 0;
            *ptr = nullptr;
        }
    }

    // Clean up the child at offset 0x10C again
    void* child = *(void**)((char*)this + 0x10C);
    if (child != nullptr) {
        *(int*)(child + 8) = 0;
        *(void**)((char*)this + 0x10C) = nullptr;
    }

    // Final cleanup
    FUN_0085a670();
    FUN_009af250();
}