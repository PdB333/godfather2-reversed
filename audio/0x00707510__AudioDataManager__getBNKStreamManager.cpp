// FUNC_NAME: AudioDataManager::getBNKStreamManager
// Address: 0x00707510
// Returns the BNKStreamManager pointer stored at offset 0x2BC, or a global default if null.

#include <cstdint>

class BNKStreamManager;

extern BNKStreamManager* g_pDefaultBNKStreamManager; // Address 0x0120546e

class AudioDataManager {
public:
    // Offset +0x2BC: pointer to the BNK stream manager
    BNKStreamManager* m_pBNKStreamManager;

    BNKStreamManager* getBNKStreamManager() {
        BNKStreamManager* result = this->m_pBNKStreamManager;
        if (result == nullptr) {
            result = g_pDefaultBNKStreamManager;
        }
        return result;
    }
};