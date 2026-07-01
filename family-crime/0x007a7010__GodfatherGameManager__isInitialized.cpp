// FUNC_NAME: GodfatherGameManager::isInitialized
// Address: 0x007a7010
// Role: Checks if the GodfatherGameManager singleton has been initialized by retrieving a global flag pointer.

bool GodfatherGameManager::isInitialized()
{
    // The callee FUN_006a7890 is a system function that returns a pointer to a flag
    int* flagPtr = (int*)GetGlobalFlagPtr();
    return *flagPtr != 0;
}