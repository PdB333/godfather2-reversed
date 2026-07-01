// FUNC_NAME: PlayerSM::applyAction
// Address: 0x0079d2f0
// Role: Handles action requests on the player state machine, checking game pause and component state,
// then dispatching to the appropriate animation clip based on action type.

#include <cstdint>

// Forward declarations of helper functions (defined elsewhere)
bool isGamePaused();                                                          // 0x00481640
bool isActionAllowed(AnimationComponent* pAnim);                              // 0x00444a80
void playAnimation(AnimationComponent* pAnim, AnimClip* pClip);               // 0x00444660

// Structure: AnimationComponent (offsets are hypothetical)
struct AnimationComponent {
    // ... members
};

// Structure: ActorInterface (used via QueryInterface with GUID 0x55859efa)
struct ActorInterface {
    // offset 0x239*4 (0x8E4): bit 13 = some state flag (e.g., kFlagInactive)
    // offset 0x238*4 (0x8E0): bit 11 = another state flag
};

class PlayerSM {
public:
    // +0x2498: pointer to AnimationComponent
    AnimationComponent* m_pAnimComponent;

    // +0x2AB8 - 0x2AE0: animation clip pointers (6 entries, 8 bytes apart)
    AnimClip* m_pActionAnim0;       // +0x2AB8
    AnimClip* m_pActionAnim1;       // +0x2AC0
    AnimClip* m_pActionAnim2;       // +0x2AC8
    AnimClip* m_pActionAnim3;       // +0x2AD0
    AnimClip* m_pActionAnim4;       // +0x2AD8
    AnimClip* m_pActionAnim5;       // +0x2AE0

    void applyAction(uint8_t actionType, void** ppActorInterface);
};

void __thiscall PlayerSM::applyAction(uint8_t actionType, void** ppActorInterface)
{
    // Check if game is paused and if the animation component allows actions
    if (!isGamePaused() && isActionAllowed(m_pAnimComponent))
    {
        // Optionally check the actor interface for blocking states
        if (ppActorInterface != nullptr)
        {
            int* pObj = *ppActorInterface;       // Get object pointer
            ActorInterface* pActorInterface = nullptr;
            bool queryResult = (**(code**)(*pObj + 0x10))(0x55859efa, &pActorInterface); // QueryInterface
            if (queryResult && pActorInterface != nullptr)
            {
                uint32_t flags1 = reinterpret_cast<uint32_t*>(pActorInterface)[0x239]; // +0x8E4
                uint32_t flags2 = reinterpret_cast<uint32_t*>(pActorInterface)[0x238]; // +0x8E0
                // If either blocking flag is set, refuse the action
                if (((flags1 >> 0xD) & 1) || ((flags2 >> 0xB) & 1))
                    return;
            }
        }

        // Map action type to the corresponding animation clip
        AnimClip* pClip = nullptr;
        switch (actionType)
        {
        case 0:
        case 7:
            pClip = m_pActionAnim0;
            break;
        case 1:
        case 8:
            pClip = m_pActionAnim1;
            break;
        case 2:
        case 4:
            pClip = m_pActionAnim2;
            break;
        case 3:
        case 5:
            pClip = m_pActionAnim3;
            break;
        case 6:
            pClip = m_pActionAnim4;
            break;
        case 9:
            pClip = m_pActionAnim5;
            break;
        default:
            return;
        }
        playAnimation(m_pAnimComponent, pClip);
    }
}