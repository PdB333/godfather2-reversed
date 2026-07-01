// FUNC_NAME: SomeManager::registerComponent

void __fastcall SomeManager::registerComponent(void* param_1) // param_1 is likely 'this' pointer
{
    char isSystemReady = FUN_00481660(); // Check if system is ready
    if (isSystemReady) {
        int allocatedBlock = FUN_009c8e50(0x38); // Allocate memory for component (size 0x38)
        if (allocatedBlock != 0) {
            void* componentPointer = FUN_008a9800(param_1); // Create component using this manager
            FUN_00481690(componentPointer); // Register the component
            return;
        }
        FUN_00481690(0); // Register null on allocation failure
    }
    return;
}