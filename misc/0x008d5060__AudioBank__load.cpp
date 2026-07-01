// FUNC_NAME: AudioBank::load
// Function address: 0x008d5060
// Role: Loads audio bank data from a global pointer into the object's buffer, sets loaded flag.
// This is a one-time initialization; the flag at +0x81 prevents reloading.

class AudioBank {
public:
    // +0x4c: Data buffer (0x8000 bytes)
    // +0x81: Loaded flag (bool)
    void load() {
        if (*(char*)(this + 0x81) == '\0') {
            if (g_pAudioData != 0) {
                // Copy 0x8000 bytes from global audio data into this object's buffer
                copyData(this + 0x4c, g_pAudioData, 0x8000);
            }
            *(char*)(this + 0x81) = 1; // Mark as loaded
        }
    }
};

// Global pointer to raw audio data (DAT_0112f9dc)
extern void* g_pAudioData;

// Helper function (FUN_00408900) - likely memcpy or file read
void copyData(void* dest, void* src, int size);