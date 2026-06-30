// FUNC_NAME: dispatchToGlobalManager
// Address: 0x005e6550
// Role: Thin wrapper that forwards a parameter to a global object's method.
// DAT_012234bc is likely a singleton manager pointer (e.g., GodfatherGameManager, AudioDataManager).
void dispatchToGlobalManager(int param)
{
    // Forward the call to the actual implementation.
    FUN_005e49d0(DAT_012234bc, param);
    return;
}