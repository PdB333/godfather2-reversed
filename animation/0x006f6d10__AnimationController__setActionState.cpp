// FUNC_NAME: AnimationController::setActionState

// Function address: 0x006f6d10
// Role: Sets or triggers an animation action based on the action type.
// Uses an internal state (+0xe4) to select the appropriate animation handle.
// Calls a global animation manager singleton to play/stop animations.

#include <cstdint>

// Forward declarations for the animation manager virtual table structure
class AnimationManager;
AnimationManager* GetAnimationManager(); // Wrapper for FUN_0043b870(DAT_0112a9fc)

class AnimationController {
public:
    // +0x7c: Handle for the animation currently playing (when state == 1)
    int m_currentAnimationHandle;
    // +0x84: Handle for a queued/alternate animation (when state == 2)
    int m_queuedAnimationHandle;
    // +0xe4: Internal animation state (1 = playing, 2 = stopped)
    int m_animationState;

    // Action types:
    // 1 = Play (calls AnimationManager::play())
    // 2 = Stop (sets state to 2 and returns, no animation manager call)
    // 3 = Play with speed 1.0 (calls AnimationManager::playWithSpeed(1.0f))
    void setActionState(int actionType);
};

void __thiscall AnimationController::setActionState(int actionType)
{
    int handle;
    AnimationManager* mgr;

    // Handle stop action first (actionType == 2)
    if (actionType != 1) {
        if (actionType == 2) {
            m_animationState = 2;
            return;
        }
        if (actionType != 3) {
            return; // Unknown action type, ignore
        }
        // Fall through for actionType == 3 (or 1 after the first check)
    }

    // Select handle based on current state
    if (m_animationState == 1) {
        handle = m_currentAnimationHandle;
    } else if (m_animationState == 2) {
        handle = m_queuedAnimationHandle;
    } else {
        return; // Invalid state
    }

    // Check if handle is valid (not 0 and not the sentinel 0x48)
    if (handle != 0 && handle != 0x48) {
        mgr = GetAnimationManager();
        if (mgr != nullptr) {
            if (actionType == 3) {
                // Call virtual function at vtable+0x20: play with speed (1.0f)
                (**(void (__thiscall**)(AnimationManager*, float))(*mgr + 0x20))(mgr, 1.0f);
            } else {
                // Call virtual function at vtable+0x1c: play (no params)
                (**(void (__thiscall**)(AnimationManager*))(*mgr + 0x1c))(mgr);
            }
        }
    }
}