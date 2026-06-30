// FUNC_NAME: cleanupStaticManagers
extern void destroyManagerInstance(void* ptr);

// Global static manager objects (addresses from Ghidra: 0x0112ac74, 0x0112abd8, 0x0112ac64, 0x0112ac5c, 0x0112ac6c)
extern char g_manager1; // placeholder for the actual object
extern char g_manager2;
extern char g_manager3;
extern char g_manager4;
extern char g_manager5;

void cleanupStaticManagers(void)
{
    destroyManagerInstance(&g_manager1);
    destroyManagerInstance(&g_manager2);
    destroyManagerInstance(&g_manager3);
    destroyManagerInstance(&g_manager4);
    destroyManagerInstance(&g_manager5);
}