// FUNC_NAME: NPC::randomizeBehaviorFlags

void NPC::randomizeBehaviorFlags()
{
    uint32_t randVal;
    float scaledFloat;

    // 50% chance to set "actionA" flag (bit 18)
    randVal = rand();
    if ((randVal & 1) == 0)
    {
        m_behaviorFlags |= 0x40000; // +0x1f5c bit 18
    }

    // Second random decision
    randVal = rand();
    if ((randVal & 0x800) == 0 || (m_stateFlagsByte & 1) != 0) // +0x1f54 bit 0 overrides random
    {
        scaledFloat = (float)rand() * g_randScaleFactor; // g_randScaleFactor = 1.0f/RAND_MAX
        if (scaledFloat >= g_behaviorThreshold1) // DAT_00d5ef50
        {
            if (scaledFloat >= g_behaviorThreshold2) // DAT_00e4497c
            {
                m_behaviorFlags |= 0x100000; // +0x1f5c bit 20
            }
            else
            {
                m_behaviorFlags |= 0x80000; // +0x1f5c bit 19
            }
        }
        // else: no flag set from this branch
    }
    else
    {
        m_behaviorFlags |= 0x200000; // +0x1f5c bit 21
    }

    // 50% chance to set "actionC" flag (bit 23)
    randVal = rand();
    if ((randVal & 1) != 0)
    {
        m_behaviorFlags |= 0x800000; // +0x1f5c bit 23
    }

    // 50% chance to set "actionD" flag (bit 22)
    randVal = rand();
    if ((randVal & 1) == 0)
    {
        m_behaviorFlags |= 0x400000; // +0x1f5c bit 22
    }
}