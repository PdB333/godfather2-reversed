// FUNC_NAME: EARSObject::queryFrameworkManager
void EARSObject::queryFrameworkManager(void)
{
    // Retrieve the manager pointer stored at offset 0x100 of this object
    void** managerPtr = *(void***)((int)this + 0x100);
    // Magic constant identifying the desired interface (e.g., IFrameworkManager)
    const unsigned int interfaceId = 0x55859efa;
    void* singleton = nullptr;

    // Call virtual function at vtable index 4 (vtable+0x10) on the manager object
    // This is likely a QueryInterface-style method that returns a singleton/interface instance
    ((void(*)(unsigned int, void**))(*(int**)managerPtr)[4])(interfaceId, &singleton);

    // Write the magic constant to the first DWORD of the retrieved singleton as a signature
    *(unsigned int*)singleton = interfaceId;
}