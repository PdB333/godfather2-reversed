// FUNC_NAME: GodfatherGameManager::setActiveFlag
void __thiscall GodfatherGameManager::setActiveFlag(GodfatherGameManager* this)
{
    // +0x1f18: active flag (int, set to 1)
    *(int*)((uint8_t*)this + 0x1f18) = 1;
}