// FUNC_NAME: ShutdownGlobalSingleton
void ShutdownGlobalSingleton(void)
{
    // Global pointer to a singleton object (likely a manager)
    if (gSomeSingletonPtr != nullptr) {
        // Call the first virtual function (index 0) with argument 1 (shutdown/cleanup flag)
        reinterpret_cast<void(__cdecl *)(int)>(*reinterpret_cast<uint32_t*>(*gSomeSingletonPtr))(1);
    }
}