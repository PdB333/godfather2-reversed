// FUNC_NAME: registerModule
void registerModule(void)
{
    // Call a function from the module's vtable at offset 4 (likely a constructor or factory)
    undefined4 result = (*(code **)(PTR_PTR_011259c0 + 4))();
    
    // Convert the result and store in a global (likely a module ID or handle)
    g_moduleHandle = FUN_0060d740(result);
    
    // Call another function from the vtable at offset 0x10 (likely a destructor or cleanup)
    (*(code **)(PTR_PTR_011259c0 + 0x10))();
    
    // Update the global module registration list
    g_lastRegisteredModule = DAT_012058ec;          // Save previous head
    g_moduleRegistrationCounter = g_moduleRegistrationCounter + 1; // Increment counter
    DAT_012058ec = &PTR_PTR_011259c0;               // Set new head to this module's vtable
    g_moduleRegistrationIndex = g_moduleRegistrationCounter; // Store current counter as index
}