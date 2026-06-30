// FUNC_NAME: GodfatherGameManager::markInitialized
// Function address: 0x00565ff0
// Role: Sets an initialization flag at offset 0x8048 in the game manager instance.

void __thiscall GodfatherGameManager::markInitialized(void)
{
    // Set the byte at offset 0x8048 to 1, indicating initialization is complete.
    // Offset 0x8048 is likely a boolean 'initialized' flag within the manager.
    *reinterpret_cast<unsigned char*>(reinterpret_cast<uintptr_t>(this) + 0x8048) = 1;
}