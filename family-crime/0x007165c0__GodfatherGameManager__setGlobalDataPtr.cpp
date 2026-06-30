// FUNC_NAME: GodfatherGameManager::setGlobalDataPtr
void __thiscall GodfatherGameManager::setGlobalDataPtr()
{
    // +0x38C: store the global pointer (likely g_gameManager or similar singleton)
    *(int*)((int)this + 0x38C) = DAT_01205228;
}