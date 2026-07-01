// FUNC_NAME: checkFlagAndProcess
void __fastcall checkFlagAndProcess(int param_1)
{
    int iVar1;
    
    // If param_1 is zero, use null pointer; otherwise get pointer from global manager
    if (param_1 == 0) {
        iVar1 = 0;
    }
    else {
        iVar1 = FUN_0043b870(DAT_0112af98); // getObjectFromManager(g_someManager)
    }
    
    // Check if bit 0 at offset 0x50 is set (active/dirty flag)
    if ((~*(byte *)(iVar1 + 0x50) & 1) == 0) {
        FUN_007894e0(); // triggerAction()
        return;
    }
    return;
}