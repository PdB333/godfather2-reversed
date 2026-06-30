// FUN_NAME: SoundInstance::stopAndRelease (0x005df430)
// Releases and stops two sound streams managed by this SoundInstance.
// The class holds pointers to two SoundSource manager objects (+0x0c and +0x04)
// and corresponding resource handles (+0x10 and +0x08).
// Each manager's vtable has release(resource, 0) at +0x04 and stop() at +0x0c.
class SoundInstance {
public:
    // Virtual function table for the SoundSource manager sub-object
    struct SoundSourceVTable {
        void (*release)(void* resource, int zero); // +0x04
        void (*stop)();                             // +0x0c
    };

    // Field offsets (relative to this):
    // +0x04: m_soundSource2  (pointer to second SoundSource manager)
    // +0x08: m_stream2       (opaque resource handle to release)
    // +0x0c: m_soundSource1  (pointer to first SoundSource manager)
    // +0x10: m_stream1       (opaque resource handle to release)
    SoundSourceVTable** m_soundSource2; // +0x04
    void* m_stream2;                    // +0x08
    SoundSourceVTable** m_soundSource1; // +0x0c
    void* m_stream1;                    // +0x10

    void stopAndRelease() {
        // Release first stream resource
        if (m_stream1 != nullptr) {
            SoundSourceVTable* vt1 = *m_soundSource1;
            vt1->release(m_stream1, 0);
            m_stream1 = nullptr;
        }
        // Stop the first manager
        SoundSourceVTable* vt1 = *m_soundSource1;
        vt1->stop();

        // Release second stream resource
        if (m_stream2 != nullptr) {
            SoundSourceVTable* vt2 = *m_soundSource2;
            vt2->release(m_stream2, 0);
            m_stream2 = nullptr;
        }
        // Stop the second manager
        SoundSourceVTable* vt2 = *m_soundSource2;
        vt2->stop();
    }
};