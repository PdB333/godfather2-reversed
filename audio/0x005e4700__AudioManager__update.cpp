// FUNC_NAME: AudioManager::update
#include <cstdint>

struct SoundSlot {
    void* pSound;       // +0x00: pointer to sound object
    int soundId;        // +0x04: sound identifier
    int state;          // +0x08: 0=idle, 1=ready, 2=playing, 3=paused
};

// Global variables (inferred from decompilation)
extern int g_pauseVolume;           // DAT_012056c4
extern float g_listenerPos[3];      // DAT_011a0ed8, DAT_011a0ec0 (likely x,y,z)
extern float g_dopplerFactor;       // DAT_011a0ee4
extern int g_masterVolume;          // DAT_0120569e
extern void* g_pauseChecker;        // DAT_01223510: pointer to object with vtable

// Forward declarations of called functions (incomplete signatures)
void FUN_005e45d0(char* outBuffer);               // fills a 32-byte buffer with audio environment data
void FUN_005e5f10(void* slotBase);                // resets a sound slot
void FUN_005e61a0(void* slotBase, char* buffer);  // updates sound slot with environment data
void FUN_005f1d60(uint32_t deltaTime);            // updates global audio time/delta
void FUN_005f0ee0(float* outListenerPos, float* inListenerPos); // computes listener position/doppler

// AudioManager class (assumed)
class AudioManager {
public:
    SoundSlot* getSoundSlots() const { return reinterpret_cast<SoundSlot*>(reinterpret_cast<char*>(this) + 0x20); }
    int getNumSoundSlots() const { return 512; } // 0x200

    void** getUpdateListeners() const { return reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x6020); }
    int getNumUpdateListeners() const { return *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x6024); }

    int update(uint32_t deltaTime);
};

int AudioManager::update(uint32_t deltaTime) {
    // Notify all registered listeners of an update cycle
    int numListeners = this->getNumUpdateListeners();
    if (numListeners != 0) {
        void** listeners = this->getUpdateListeners();
        for (int i = 0; i < numListeners; ++i) {
            void* listener = listeners[i];
            if (listener != nullptr) {
                // Call virtual function at offset 4 (likely onUpdate)
                (*(void(**)(void*))(*reinterpret_cast<int*>(listener) + 4))(listener);
            }
        }
    }

    // Zero out a 64-byte temporary buffer (possibly a 4x4 matrix or 16 floats)
    float tempMatrix[16] = {0};

    // Fill a 32-byte buffer with audio environment data (e.g., listener position/orientation)
    char environmentBuffer[32];
    FUN_005e45d0(environmentBuffer);

    // Iterate over all sound slots
    SoundSlot* slots = this->getSoundSlots();
    for (int i = 0; i < 512; ++i) {
        SoundSlot& slot = slots[i];
        if (slot.state == 2) { // Playing
            void* slotBase = reinterpret_cast<char*>(&slot) - 4; // Compiler adjustment: slotBase points to beginning of the struct
            FUN_005e5f10(slotBase); // Reset slot
            FUN_005e61a0(slotBase, environmentBuffer); // Update slot with environment
            if (slot.pSound != nullptr) {
                // Clear sound flags at offsets +0x58 and +0x5a (byte and short)
                *reinterpret_cast<uint8_t*>(reinterpret_cast<char*>(slot.pSound) + 0x58) = 0xFF;
                *reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(slot.pSound) + 0x5a) = 0;
            }
        }
    }

    // Update global audio time/delta processing
    FUN_005f1d60(deltaTime);

    // Update global volume and doppler settings
    g_pauseVolume = 0x80; // Default volume (128)
    FUN_005f0ee0(&g_listenerPos[0], &g_listenerPos[1]); // Possibly compute listener position
    g_pauseVolume -= static_cast<int>(g_dopplerFactor); // Apply doppler shift
    g_masterVolume = 0; // Mute (or reset)

    // Check if the game is paused via singleton
    int (*isPaused)(void*) = reinterpret_cast<int(*)(void*)>(*reinterpret_cast<int*>(g_pauseChecker) + 0x44);
    if (isPaused(g_pauseChecker)) {
        return 1; // Return 1 to indicate pause state
    }
    return 0;
}