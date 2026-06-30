// FUNC_NAME: Character::processAction
void __thiscall Character::processAction(int *pAction)
{
    float fActionPos[3]; // returned by pAction->getPosition()
    float fTmp;
    int iCurrentFrame = g_nCurrentFrame;
    int iLastFrame;
    int *pLastAction;

    if (pAction == nullptr)
        return;

    iLastFrame = *(int *)(this + 0x204); // m_nLastProcessedFrame
    pLastAction = *(int **)(this + 0x208); // m_pLastProcessedAction

    // Check timing: if last action was processed on a different frame and the time elapsed is too short, skip
    if (iLastFrame != 0 && (iCurrentFrame != iLastFrame || pAction != pLastAction))
    {
        float fFrameDiff = (float)(iCurrentFrame - iLastFrame);
        if (iCurrentFrame - iLastFrame < 0)
            fFrameDiff += g_nFrameWrap;
        if (fFrameDiff * g_fTimeScale < *(float *)(this + 0x1c8)) // m_fMinTimeBetweenActions
            return;
    }

    // Check action flags (0x14 = 0x10 | 0x4)
    if ((*(uint *)(this + 0x1c4) & 0x14) != 0) // m_nActionFilterFlags
    {
        // Get position from action (virtual method at vtable offset 0x4c)
        (**(code **)(*pAction + 0x4c))(&fActionPos[0]); // returns fActionPos[0], [1], [2] as x,y,z

        // If filter flag 0x10 is set, check if action position is too close (squared distance)
        if ((*(uint *)(this + 0x1c4) & 0x10) != 0)
        {
            float fSqDist = fActionPos[0]*fActionPos[0] + fActionPos[1]*fActionPos[1] + fActionPos[2]*fActionPos[2];
            if (fSqDist < *(float *)(this + 0x20c)) // m_fMinSqDistToAction
                return;
        }

        // If filter flag 0x4 is set, check dot product with forward vector (0x1a0,0x1a4,0x1a8)
        if ((*(uint *)(this + 0x1c4) & 4) != 0)
        {
            float fDot = *(float *)(this + 0x1a0) * fActionPos[0] + 
                         *(float *)(this + 0x1a4) * fActionPos[1] + 
                         *(float *)(this + 0x1a8) * fActionPos[2];
            if (fDot <= 0.0f)
            {
                if (*(int *)(this + 0x1ec) == 0) // m_nAllowBackwardAction
                    return;
                // Update last action tracking
                *(int **)(this + 0x208) = pAction;
                *(int *)(this + 0x204) = iCurrentFrame;

                if (*(float *)(this + 500) > 0.0f) // m_fActionDelay
                {
                    // Launch delayed action
                    int hAction = (FUN_009c8e50(0xc) != 0) ? FUN_0045ca00(pAction) : 0;
                    FUN_00440590(&DAT_012180f0, this + 0x3c, *(undefined4 *)(this + 500), hAction, 0);
                    return;
                }
                // Immediate action without delay
                FUN_0045ca00(pAction);
                FUN_00408bb0(&DAT_012180f0, this + 0x3c, local_14, 0);
                FUN_0045cac0();
                return;
            }
        }
    }

    // Default path: update last action, then either immediate or delayed
    *(int **)(this + 0x208) = pAction;
    *(int *)(this + 0x204) = iCurrentFrame;

    if (*(float *)(this + 500) <= 0.0f) // m_fActionDelay
    {
        FUN_0045ca00(pAction);
        FUN_00408bb0(&DAT_012180f8, this + 0x3c, local_14, 0);
        FUN_0045cac0();
        return;
    }

    // Delayed action with different data (DAT_012180f8)
    int hAction = (FUN_009c8e50(0xc) != 0) ? FUN_0045ca00(pAction) : 0;
    FUN_00440590(&DAT_012180f8, this + 0x3c, *(undefined4 *)(this + 500), hAction, 0);
}