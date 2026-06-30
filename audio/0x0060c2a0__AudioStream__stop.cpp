// FUNC_NAME: AudioStream::stop

// Function address: 0x0060c2a0
// This function appears to be a member function of an audio stream node (AudioStream).
// It releases internal resources and signals completion via a callback.

struct AudioStream {
    void* m_pCallback;          // +0x00: pointer to a callback or state (checked for non-zero)
    int* m_pBuffer1;            // +0x1C: (field at this[7])  first buffer pointer
    int* m_pBuffer2;            // +0x20: (field at this[8])  second buffer pointer
    int* m_pSomething;          // +0x24: (field at this[9])  another pointer
    byte  m_bStopped;           // +0x28: (field at this[10]) stop flag
};

// External function: releases or cleans up internal buffer(s)
// Address: 0x0060be80
void __cdecl releaseInternalBuffer(int* pBuffer1, int* pSomething);

// Global table pointer (likely a vtable for audio manager callbacks)
// Address: 0x01205868
extern void* g_pAudioManagerVTable;

void __thiscall AudioStream::stop(void) {
    // Release internal buffers
    releaseInternalBuffer(this->m_pBuffer1, this->m_pSomething);

    // If a callback is registered, invoke it and reset state
    if (this->m_pCallback != 0) {
        // Call function at offset 4 of the global vtable (likely OnStreamStopped)
        void (*onStreamStopped)(int*, int*) = (void (*)(int*, int*))((void**)g_pAudioManagerVTable)[1];
        onStreamStopped(this->m_pBuffer1, this->m_pBuffer2);

        // Clear the buffer pointer and mark as stopped
        this->m_pBuffer1 = 0;
        this->m_bStopped = 1;
    }
}