//FUNC_NAME: getGlobalManager
// Returns a global pointer stored at 0x0120589c. Used by multiple subsystems to access a singleton manager.
void* getGlobalManager(void)
{
    return gGlobalManagerPointer;
}