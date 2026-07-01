// FUNC_NAME: GodfatherGameManager::setMaxRespect
void __fastcall GodfatherGameManager::setMaxRespect(int thisPtr)
{
    // Set max respect value at offset +0x2C80
    // DAT_00d6a54c is likely a global constant for maximum respect
    *(int*)(thisPtr + 0x2C80) = DAT_00d6a54c;
    return;
}