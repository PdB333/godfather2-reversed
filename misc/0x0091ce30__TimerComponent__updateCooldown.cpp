// FUNC_NAME: TimerComponent::updateCooldown
// Address: 0x0091ce30
// Role: Checks if a cooldown timer is expired and updates its internal state, then delegates to base update.

void __thiscall TimerComponent::updateCooldown(TimerComponent* this, int* pTimeA, int timeB, int param4, int param5)
{
    // If cooldown is not currently active
    if (!this->m_bCooldownActive)          // +0x94: bool flag
    {
        int currentTime = getCurrentTime(); // FUN_009185a0: returns game time (ms or tick)
        // Check if the sum of external times is within a 10-unit window of current time
        if ((currentTime - 10U) <= (uint)(*pTimeA + timeB))
        {
            // Set new cooldown intervals relative to base duration
            this->m_cooldownTime2 = this->m_baseCooldownDuration + 1; // +0x9c
            this->m_cooldownTime1 = this->m_baseCooldownDuration + 5; // +0x98
            onCooldownExpired(); // FUN_0091cd80(0,0): callback (e.g., start cooldown or notify)
        }
    }
    // Call base class update with remaining parameters
    baseUpdate(pTimeA, timeB, param4, param5); // FUN_0095c5d0
}