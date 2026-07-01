// FUNC_NAME: Sentient::isActionPermitted
// Address: 0x007d8b20
// Role: Checks if the sentient is allowed to perform an action based on internal state flags,
// game manager status, and menu state. Returns true if allowed.

#include <cstdint>

// Forward declarations for global data (assumed from THECALL)
extern void* g_pMenuManager; // DAT_0112a838 - global pointer to menu manager
extern void* getGameManager(); // FUN_007ab160 - returns pointer to game manager singleton

// The sentient object has a pointer to a state structure at offset 0x74.
// The state structure contains flags at offset +4 (byte), bit 5 (0x20) indicates active/intent.
struct SentientState {
    uint8_t _pad0[4];     // offset 0-3
    uint8_t flags;        // offset 4: bit5 = 0x20 (active)
};

// The game manager has flags at offset +4, bit 1 (0x02) indicates something like "in game"?
// Actually bit 2 (0x04) is checked.
struct GameManager {
    uint8_t _pad0[4];     // offset 0-3
    uint8_t flags;        // offset 4: bit2 = 0x04 (likely "gameIsRunning" or "isPlaying")
};

// Sentient class (partial definition)
class Sentient {
public:
    bool isActionPermitted() const;

private:
    uint8_t _pad0[0x74];              // unknown data before state pointer
    SentientState* m_pState;          // +0x74: pointer to state flags
};

bool Sentient::isActionPermitted() const {
    // Check if sentient has active intent flag in state
    if (m_pState != nullptr && (m_pState->flags & 0x20) != 0) {
        GameManager* pGameMgr = static_cast<GameManager*>(getGameManager());
        // Check if game manager exists and bit 2 (0x04) is set (e.g., "in gameplay")
        if (pGameMgr != nullptr && (reinterpret_cast<uint8_t*>(pGameMgr)[4] & 0x04) != 0) {
            // Allow action if no menu is active (menu manager null or current menu handle is zero)
            if (g_pMenuManager == nullptr || *reinterpret_cast<int32_t*>(static_cast<char*>(g_pMenuManager) + 0x5c) == 0) {
                return true;
            }
        }
    }
    return false;
}