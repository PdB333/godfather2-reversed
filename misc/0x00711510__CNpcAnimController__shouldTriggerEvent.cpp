// FUNC_NAME: CNpcAnimController::shouldTriggerEvent
bool __thiscall CNpcAnimController::shouldTriggerEvent(void)
{
    float fVar1;
    float fVar2;
    int *piVar3;
    float fRandomThreshold;
    float fResult;
    int iRandom;
    bool bRet;

    fResult = 0.0f;
    if (this->m_pAnimData != NULL) {
        if (!this->m_bAnimPlaying) {
            fResult = g_currentTime - this->m_fAnimTime;
            if (this->m_iFlags != 0) {
                fResult = fResult * g_scaleFactor1;
            }
            piVar3 = (int *)GetTimeManager();
            fVar1 = (*(float (__thiscall **)(int))(*(int *)(*piVar3) + 0x30))();
            fResult = fResult / fVar1; // normalize by delta time
        }
        else {
            fResult = g_otherConstant;
        }
    }
    iRandom = rand();
    if ((float)iRandom * g_randomCompareScale < fResult) {
        return true;
    }
    return false;
}