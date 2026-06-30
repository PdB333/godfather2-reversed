// FUNC_NAME: EntityManager::lazyInitComponent
void EntityManager::lazyInitComponent(void* obj) // obj at offset +0 is vtable, +2 short flag
{
    // Call base manager update
    baseManagerUpdate();

    // Check if component is uninitialized (short at offset +2 == 0)
    if (*(short*)((char*)obj + 2) == 0)
    {
        // Attempt to create a new component instance
        void* newComponent = createComponent(); // FUN_0059c450
        if (newComponent != 0)
        {
            // Perform additional setup on the new component
            setupComponent(); // FUN_005ab430

            // Register component via global function pointer (likely addComponent)
            // The constant 0x58 may represent a component type ID or slot index
            g_globalFunctionPtr(newComponent, 0x58); // DAT_0119caf8
        }
    }
}