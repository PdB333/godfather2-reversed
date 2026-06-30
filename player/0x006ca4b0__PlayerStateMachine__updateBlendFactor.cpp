// FUNC_NAME: PlayerStateMachine::updateBlendFactor

void __thiscall PlayerStateMachine::updateBlendFactor(int this, int *pContextObject, float deltaTime)
{
    // +0x7c: bool m_bBlendTarget (0 = decrease, 1 = increase)
    // +0x80: float m_fBlendValue (current blend progress, clamped to [0.0, g_fMaxBlend])
    // Global fade speed and max blend values
    extern float g_fFadeSpeed;   // DAT_00d5f040
    extern float g_fMaxBlend;    // _DAT_00d5780c (likely 1.0f)
    extern int *g_pGameState;    // DAT_012233a0 (pointer to a global game state object)

    // Check condition via virtual call on context object (hash 0x55859efa)
    // This likely determines whether to blend toward 0 or 1.
    bool bCondition = pContextObject->CheckCondition(0x55859efa);
    if (bCondition)
    {
        // Additional global check? (maybe from a different source)
        // The decompiled code shows a second condition here, possibly a global override.
        // For simplicity, assume it's a redundant check or leftover from inlining.
        // Original: if (bCondition && (&stack != &DAT_00000004)) { ... }
        // We'll keep the logic: if condition true, set target to 1.
        *(bool *)(this + 0x7c) = true;
    }
    else
    {
        *(bool *)(this + 0x7c) = false;
    }

    // Check a global flag (bit 5 at offset 0x56c of a game state object)
    int *pStateObject = *(int **)(g_pGameState + 4);
    if (pStateObject && pStateObject != (int *)0x1f30 && (*(uint *)(pStateObject + 0x56c) & (1 << 5)) != 0)
    {
        // If the global flag is set, snap the blend value directly to 0 or 1
        *(float *)(this + 0x80) = (float)*(bool *)(this + 0x7c);
        return;
    }

    // Otherwise, smoothly interpolate the blend value
    bool bTarget = *(bool *)(this + 0x7c);
    float *pBlend = (float *)(this + 0x80);
    if (bTarget == false)
    {
        *pBlend -= deltaTime * g_fFadeSpeed;
    }
    else
    {
        *pBlend += deltaTime * g_fFadeSpeed;
    }

    // Clamp between 0.0 and g_fMaxBlend
    if (*pBlend < 0.0f)
    {
        *pBlend = 0.0f;
    }
    else if (*pBlend > g_fMaxBlend)
    {
        *pBlend = g_fMaxBlend;
    }
}