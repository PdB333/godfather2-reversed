// FUNC_NAME: dispatchToActiveManager
void __fastcall dispatchToActiveManager(uint param)
{
    int* pTarget;
    
    if (g_pActiveManager == 0) {
        pTarget = *(int**)(g_pAlternateManager + 0x20); // +0x20: pointer to target object
    } else {
        pTarget = *(int**)(g_pActiveManager + 0x18); // +0x18: pointer to target object
    }
    
    if (pTarget != 0) {
        dispatchEvent(g_pSomeGlobalObject, pTarget, param);
    }
}