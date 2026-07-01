// FUNC_NAME: PlayerManager::tryShowTutorial
#include <cstdint>

// Forward declarations for callees
extern void updateGlobalState(void);
extern int getLocalPlayer(void); // Returns a pointer to Player or 0
extern void triggerTutorialHint(void);

// Player class struct with known offsets
class Player {
public:
    // Fields up to offset 0x1f58
    uint32_t m_flags; // +0x1f58
    // ... other members
};

bool PlayerManager::tryShowTutorial() {
    updateGlobalState();

    Player* player = reinterpret_cast<Player*>(getLocalPlayer());
    if (player != nullptr) {
        // Check if the tutorial flag (bit 25) is not set
        if ((player->m_flags & (1 << 25)) == 0) {
            triggerTutorialHint();
            return true;
        }
    }
    return false;
}