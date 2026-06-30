// FUNC_NAME: GodfatherGameManager::resetFieldAt20
// Function address: 0x006817d0
// Role: Resets a field at offset 0x20 in the global game manager singleton

// Global singleton pointer to the main game manager
extern void* g_pGodfatherGameManager;

// Forward declaration of a subsystem initialization function called before reset
void InitSubSystem(void);

void GodfatherGameManager::resetFieldAt20(void)
{
    // +0x20 offset from the base of the game manager (likely a pointer or counter)
    int* field = (int*)((char*)g_pGodfatherGameManager + 0x20);
    
    // Call initialization logic for the subsystem
    InitSubSystem();
    
    // Clear the field (set to 0) after initialization
    *field = 0;
}