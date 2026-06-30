// FUNC_NAME: Player::setupActionCommand
// Function address: 0x0075d650
// Purpose: Fills an action command structure (5 integer output) based on the current player's animation state.
// Offsets used:
//   this+0x58 : m_pCharacter (pointer to main character object)
//   m_pCharacter+0x1e88 : m_animationId (current animation ID)
//   m_pCharacter+0x1e90 : m_animationParam (additional animation parameter, e.g., sequence index)
//   m_pCharacter+0x8ec : m_flags (bitfield; bit 3 checked)
// Global constant DAT_00e4458c : g_kDefaultActionParam (assumed default value)

const int g_kDefaultActionParam = *reinterpret_cast<const int*>(0x00e4458c);
const int kAnimationNone = 0x48; // Value indicating no active animation (idle/stop)

// Constants for action modes
enum ActionMode {
    kActionMode_Idle   = 1,
    kActionMode_Active = 2
};

// Struct representing the output command parameters (5 ints)
struct ActionCommand {
    int* pTarget;   // [0] pointer to target (character object)
    int mode;       // [1] action mode (1=idle, 2=active)
    int defaultParam; // [2] global default parameter
    int animationId;  // [3] animation ID from character
    int errorCode;    // [4] -5 if flag check fails, else unchanged
};

void __thiscall Player::setupActionCommand(ActionCommand* pOutCmd)
{
    // Base pointer to the character object
    int* pCharacter = *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x58);

    // Fill static fields
    pOutCmd->animationId = pCharacter[0x1e88 / 4]; // offset 0x1e88
    pOutCmd->defaultParam = g_kDefaultActionParam;

    int animParam = pCharacter[0x1e90 / 4]; // offset 0x1e90 (animation parameter)

    if (animParam == 0 || animParam == kAnimationNone) {
        // No animation or idle animation
        pOutCmd->pTarget = reinterpret_cast<int*>(pCharacter);
        pOutCmd->mode = kActionMode_Idle;
    }
    else {
        // Active animation
        pOutCmd->pTarget = reinterpret_cast<int*>(pCharacter);
        animParam = pCharacter[0x1e90 / 4]; // Re-read (as per decompiled)
        if (animParam == 0) {
            *reinterpret_cast<int*>(reinterpret_cast<char*>(pOutCmd->pTarget) + 4) = 0; // some field in target at +4
            pOutCmd->mode = kActionMode_Active;
        }
        else {
            *reinterpret_cast<int*>(reinterpret_cast<char*>(pOutCmd->pTarget) + 4) = animParam - kAnimationNone;
            pOutCmd->mode = kActionMode_Active;
        }
    }

    // Check bit 3 of flags
    uint flags = pCharacter[0x8ec / 4]; // offset 0x8ec
    if ((flags >> 3) & 1) {
        pOutCmd->errorCode = -5;
    }
}