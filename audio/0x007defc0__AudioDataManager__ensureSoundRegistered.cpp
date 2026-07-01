// FUNC_NAME: AudioDataManager::ensureSoundRegistered
// Address: 0x007defc0
// Role: Checks if a specific sound hash is registered and registers it if needed

#include <cstdint>

class AudioDataManager {
public:
    // +0x58: pointer to some internal structure (e.g., resource table)
    // +0x24f8: hash table or array of registered sound IDs
    void ensureSoundRegistered();

private:
    // Internal helpers (actual addresses)
    static uint32_t getGlobalAudioHash();      // FUN_0045eea0
    static AudioInfo* getAudioInfo(int index); // FUN_0045f3b0
    static void registerAudioHash(uint32_t hash, uint32_t param2, uint32_t param3, int zero1, int zero2); // FUN_0045f020
};

// Global variable used in registration
extern uint32_t _DAT_00e53248;

void AudioDataManager::ensureSoundRegistered() {
    // Offset +0x58 is a pointer to internal data; +0x24f8 is a hash check value (0 = not registered)
    if (*(int*)(*(int*)(reinterpret_cast<uintptr_t>(this) + 0x58) + 0x24f8) == 0) {
        uint32_t hash = getGlobalAudioHash(); // e.g., current environment hash
        if (hash != 0x4f7fc948) {
            AudioInfo* info = getAudioInfo(0); // Get default audio info
            registerAudioHash(0x4f7fc948, *(uint32_t*)(reinterpret_cast<uintptr_t>(info) + 0x1c), _DAT_00e53248, 0, 0);
        }
    }
}