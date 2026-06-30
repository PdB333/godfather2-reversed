// FUNC_NAME: AudioManager::processPendingRequest
void __thiscall AudioManager::processPendingRequest(int param_2) // param_2 is priority threshold
{
    int *piVar1;
    
    // Check global audio manager state and stack availability
    if (((*(char *)(g_pAudioManager + 0x564) != 0x12) && (g_nRequestStackIndex != -1)) &&
       (g_pRequestStack[g_nRequestStackIndex] != 0)) {
        // If priority is below threshold and state allows, update audio resources
        if ((param_2 < 0xf) && (*(char *)(g_pAudioManager + 0x564) != 0x12)) {
            FUN_00411070(*(char *)(g_pAudioManager + 0x564));
            FUN_004958a0();
        }
        // Pop from request stack
        if (g_nRequestStackIndex != -1) {
            g_pCurrentRequest = g_pRequestStack[g_nRequestStackIndex];
            g_nRequestStackIndex = g_nRequestStackIndex + -1;
        }
        // Execute request via virtual function at vtable+8
        piVar1 = (int *)FUN_00411070(*(undefined1 *)(g_pAudioManager + 0x564));
        (**(code **)(*piVar1 + 8))(g_pCurrentRequest);
    }
    return;
}