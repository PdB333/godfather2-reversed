// FUNC_NAME: Player::executeAction
// Address: 0x0079d440
// Role: Handles player action commands based on action type and index, playing associated animations if conditions are met.

class Player {
public:
    // Offsets (from this):
    // +0x2498: m_pActionManager (ActionManager*)
    // +0x2a78: m_pActionAnimations[0] (Animation*)
    // +0x2a7c: m_pActionAnimations[1] (Animation*)
    // +0x2a80: m_pActionAnimations[2] (Animation*)
    // +0x8e0: m_flags0 (uint)
    // +0x8e4: m_flags1 (uint)

    void executeAction(ActionCommand* action);
};

struct ActionCommand {
    // +0x30: type (int) - action type enum, 6 means invalid
    // +0x38: index (int) - 1-based index into animation array (1-3)
    int type;
    int index;
};

// Forward declarations of external functions
bool isGamePaused(); // FUN_00481640
bool ActionManager::isReady(); // FUN_00444a80
void ActionManager::playAnimation(Animation* anim); // FUN_00444660

void Player::executeAction(ActionCommand* action) {
    // Check if game is paused
    if (isGamePaused()) {
        return;
    }

    // Check if action manager is ready
    if (!m_pActionManager->isReady()) {
        return;
    }

    // Check flags: bit 13 of m_flags1 and bit 11 of m_flags0 must be clear
    if ((m_flags1 >> 0xd & 1) != 0) {
        return;
    }
    if ((m_flags0 >> 0xb & 1) != 0) {
        return;
    }

    // Action type must not be 6 (invalid)
    if (action->type == 6) {
        return;
    }

    // Select animation based on action index (1-3)
    Animation* anim = nullptr;
    switch (action->index) {
        case 1:
            anim = m_pActionAnimations[0];
            break;
        case 2:
            anim = m_pActionAnimations[1];
            break;
        case 3:
            anim = m_pActionAnimations[2];
            break;
        default:
            return; // Invalid index
    }

    // Play the selected animation
    m_pActionManager->playAnimation(anim);
}