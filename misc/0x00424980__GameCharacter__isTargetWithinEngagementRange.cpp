// FUNC_NAME: GameCharacter::isTargetWithinEngagementRange
// 0x00424980 - Checks if the target object (stored at this+0x10) is within engagement range.
// Conditions: global max range (DAT_00e2b05c) < target's max range (+0x124) and
// target's distance metric (+0x11c) < target's max range (+0x124).
// The second condition simplifies from the original multiplication by a global scale factor.
BOOL __thiscall GameCharacter::isTargetWithinEngagementRange(void)
{
    // m_pConfig (likely AI configuration/state) at +0x154
    void* pConfig = *(void**)((int)this + 0x154);
    // m_pTarget (the target character or object) at +0x10
    void* pTarget = *(void**)((int)this + 0x10);

    if (pConfig != NULL && pTarget != NULL)
    {
        // fTargetMaxRange at target +0x124
        float fTargetMaxRange = *(float*)((int)pTarget + 0x124);
        // Global max range threshold from DAT_00e2b05c
        float fGlobalMaxRange = *(float*)0x00e2b05c;

        // Global range must be stricter (smaller) than target's own range
        if (fGlobalMaxRange < fTargetMaxRange)
        {
            // fTargetDistance at target +0x11c
            float fTargetDistance = *(float*)((int)pTarget + 0x11c);

            // Original condition: fTargetDistance * (DAT_00e2b1a4 / fTargetMaxRange) < DAT_00e2b1a4
            // With positive global scale DAT_00e2b1a4, this simplifies to fTargetDistance < fTargetMaxRange
            if (fTargetDistance < fTargetMaxRange)
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}