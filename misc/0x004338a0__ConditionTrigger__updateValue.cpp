// FUNC_NAME: ConditionTrigger::updateValue

// Global thresholds
extern float g_fThresholdHigh;  // DAT_00e2b1a4
extern float g_fThresholdLow;   // _DAT_0110ac24
extern void* g_pContext;        // DAT_012233a8 + 4 (some singleton context)

// Callbacks (forward declarations)
extern void onEnterLowState(void* context);  // FUN_00433000
extern void onExitLowState(void* context);   // FUN_00432e30

void ConditionTrigger::updateValue(float value)
{
    // Store the current value at offset +0xAC
    m_fStoredValue = value;  // +0xAC: stored float value

    if (g_fThresholdHigh <= value)
    {
        // Value is at or above the high threshold
        uint32_t flags = m_flags;  // +0x8: bitfield flags (bit2 = lowStateActive, bit3 = unknown, bit8 = belowHighThreshold)

        if ((flags & 0x4) != 0)  // lowStateActive set
        {
            // Clear low state active flag
            m_flags = flags & ~0x4;

            // Check if short at +0x2A is > -2 and bit3 (0x8) is not set
            if (m_someShort > -2 && (flags & 0x8) == 0)  // +0x2A: some short counter
            {
                onExitLowState(g_pContext);
            }
        }
        // Clear bit8 (belowHighThreshold)
        m_flags &= ~0x100;
    }
    else
    {
        // Value is below the high threshold
        m_flags |= 0x100;  // Set bit8 (belowHighThreshold)

        uint32_t flags = m_flags;  // Capture flags after setting bit8

        if (value < g_fThresholdLow)
        {
            // Below low threshold
            if ((flags & 0x4) == 0)  // lowStateActive not set
            {
                if (m_someShort > -2)  // +0x2A
                {
                    onEnterLowState(g_pContext);
                }
                m_flags |= 0x4;  // Set lowStateActive
                return;
            }
            // else: low state already active, nothing to do
        }
        else
        {
            // Value >= low threshold but still below high threshold
            if ((flags & 0x4) != 0)  // lowStateActive set
            {
                // Clear low state active flag
                m_flags &= ~0x4;

                // Check if short > -2 and bit3 (0x8) is not set (using updated flags)
                if (m_someShort > -2 && (flags & 0x8) == 0)
                {
                    onExitLowState(g_pContext);
                }
                return;
            }
            // else: low state not active, nothing to do
        }
    }
}