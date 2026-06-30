// FUNC_NAME: getGodfatherGameManagerSingleton
// Returns a global pointer to the GodfatherGameManager singleton (stored at 0x00f15a14)
extern void* g_pGodfatherGameManager; // Assuming pointer type

undefined4 getGodfatherGameManagerSingleton(void)
{
    return (undefined4)g_pGodfatherGameManager;
}