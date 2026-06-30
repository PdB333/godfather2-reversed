// FUNC_NAME: ContainerManager::initializeSlots
int __fastcall ContainerManager::initializeSlots(void* config)
{
    // Call virtual method at vtable+0xC (4th method) on this object with config as argument
    (**(code**)(*(int*)this + 0xC))(config);

    // Get pointer to child container at offset +0x04 from this
    void* childContainer = *(void**)((int)this + 4);

    // Initialize 30 slots in the child container by calling the same virtual method
    for (int i = 0; i < 0x1E; i++)
    {
        // Each call passes the slot index
        (**(code**)(*(int*)childContainer + 0xC))(i);
    }

    // Return the number of slots initialized
    return 0x1E;
}