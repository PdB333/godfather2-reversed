// FUNC_NAME: GodfatherGameManager::resetFieldAt0x1e48
void __fastcall GodfatherGameManager::resetFieldAt0x1e48(void* this)
{
    // Clear 32-bit field at offset +0x1e48 (likely a flag or counter)
    *(int*)((char*)this + 0x1e48) = 0;
}