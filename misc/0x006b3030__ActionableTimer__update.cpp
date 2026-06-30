// FUNC_NAME: ActionableTimer::update
// Address: 0x006b3030
// This function is part of a countdown timer system, likely for objectives or player actions.
// It decrements a remaining time value and triggers an associated callback when the timer expires.

void __fastcall ActionableTimer::update(ActionableTimer* this)
{
    // Check if there is an active timer target and the game is not paused/menu-open
    // +0x3d on DAT_01129904 (global game manager) is likely a "paused" or "active" flag
    if (this->m_pTimerTarget != NULL && *(char*)(DAT_01129904 + 0x3d) != '\0')
    {
        if (this->m_fTimeRemaining > 0.0f)
        {
            // Subtract frame delta time (stored in global float DAT_012067e8)
            this->m_fTimeRemaining -= DAT_012067e8;
        }
        if (this->m_fTimeRemaining <= 0.0f)
        {
            // Call the specific action function for the target (e.g., trigger event, complete objective)
            // FUN_008c7d30 signature: void __fastcall triggerAction(void* target, ActionableTimer* timer)
            triggerAction(this->m_pTimerTarget, this);
            this->m_pTimerTarget = NULL; // Clear the timer
            // Notify completion (e.g., mark timer as done, chain to next step)
            onTimerComplete();
        }
    }
}