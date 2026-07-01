// FUNC_NAME: PlayerF2FSM::updateStatusEffect
// Address: 0x00800040
// This function updates a timed status effect on the player state machine.
// It manages a tick-based decay of a cooldown value (statePtr->cooldown) 
// and tracks tick count for debug purposes.

void __thiscall PlayerF2FSM::updateStatusEffect(float time, class EffectData* statePtr)
{
    int* baseObjPtr;
    char foundFlag;
    uint foundObjID;
    float newCooldown;
    bool bHasState;

    // Check if too much time passed since last update (using global threshold)
    if (m_lastUpdateTime + DAT_00d71b10 < time)
    {
        m_tickIndex = 0;        // Reset tick index if stale
    }
    m_lastUpdateTime = time;    // Store current time

    // Only update if the associated state is active (statePtr->type == 1)
    if (statePtr->type == 1)
    {
        m_bIsActive = 1;

        if (statePtr->subType < 3)
        {
            // Check if ability bit 11 is set for quick increment
            if ((m_flags0 & 0x800) != 0)   // bit 11
            {
                m_tickCount += 1;
                goto LAB_updateAndDecay;
            }
        }
        else
        {
            // For subtype >= 3, check different flag bit
            if ((m_flags1 & 0x2000) != 0)  // bit 13
            {
                m_tickIndex = 0;
                statePtr->cooldown = 0.0f;
                goto LAB_finalChecks;
            }
            m_tickCount += 2;   // Double tick increment for higher difficulty
        }

LAB_updateAndDecay:
        // Debug logging when tick count exceeds threshold
        if (m_debugThreshold <= (uint)m_tickCount)
        {
            FUN_007f63e0(0xf);  // Output debug message
            m_tickCount = 0;
        }

        // Reduce cooldown based on current tick factor and effect strength
        newCooldown = statePtr->cooldown - 
                      m_tickDecreaseFactors[m_tickIndex] * 
                      m_effectStrength * 
                      statePtr->cooldown;
        statePtr->cooldown = newCooldown;
        if (newCooldown < 0.0f)
        {
            statePtr->cooldown = 0.0f;
        }
    }

    // Advance tick index (faster for higher subtype)
    if (statePtr->subType < 3)
    {
        m_tickIndex += 1;
    }
    else
    {
        m_tickIndex += 2;
    }

    // Clamp to maximum of 5 ticks
    if (5 < (byte)m_tickIndex)
    {
        m_tickIndex = 5;
    }

LAB_finalChecks:
    // Attempt to find a related object via hash lookup
    foundObjID = 0;
    if ((statePtr->baseObject != 0) && (statePtr->baseObject != (class BaseObject*)0x48))
    {
        baseObjPtr = (int*)((char*)statePtr->baseObject - 0x48);
        time = 0.0f;
        foundFlag = (**(code**)(*baseObjPtr + 0x10))(0x55859efa, &time);
        foundObjID = -(uint)(foundFlag != 0) & (uint)time;
    }

    // Determine if effect should be terminated (set bit 15)
    bHasState = (statePtr->type != 1) ||
                ((foundObjID != 0 && (foundObjID->someField != 0) && 
                 (foundObjID->someField != (class BaseObject*)0x48) &&
                 ((foundObjID->flags & 0x400) != 0)));  // bit 10
    if (bHasState)
    {
        if ((m_flags0 & 0x8000) == 0)   // bit 15 not set
        {
            // Call owner's method at vtable+0x28 with argument 0x20
            (**(code**)(*(int*)m_owner + 0x28))(0x20);
        }
        m_flags0 |= 0x8000;   // Mark effect as terminated
    }
    return;
}