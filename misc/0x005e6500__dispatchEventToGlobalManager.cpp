//FUNC_NAME: dispatchEventToGlobalManager
void dispatchEventToGlobalManager(uint param_1, uint param_2)
{
    // Call the actual event dispatch on the global manager instance (DAT_012234bc)
    // param_1 is ignored (possibly 'this' in some calling conventions, but not used here)
    // param_2 is the event data or identifier
    FUN_005e4950(DAT_012234bc, param_2);
    return;
}