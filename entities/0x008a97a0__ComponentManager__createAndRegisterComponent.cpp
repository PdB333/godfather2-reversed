// FUNC_NAME: ComponentManager::createAndRegisterComponent

#include <cstdint>

// Forward declarations of engine utility functions
extern bool isSystemReady();                 // FUN_00481660 - checks if engine is ready to create objects
extern void* customAlloc(uint32_t size);     // FUN_009c8e50 - custom EARS allocator (size = 0x38)
extern void* constructComponent(void* mem, uint32_t param); // FUN_008a9650 - constructor, returns initialized object
extern void registerComponent(void* component); // FUN_00481690 - registers the created component with the manager

// Creates a component (size 0x38 = 56 bytes) and registers it.
// param_1 is passed to the constructor, likely an owner ID or parent pointer.
void __fastcall ComponentManager::createAndRegisterComponent(uint32_t param)
{
    if (isSystemReady())
    {
        void* mem = customAlloc(0x38); // Allocate memory for component
        if (mem != nullptr)
        {
            void* component = constructComponent(mem, param); // Construct the component
            registerComponent(component);                     // Register with manager
            return;
        }
        // If allocation fails, register null (possibly marks failure)
        registerComponent(nullptr);
    }
    // If system not ready, silently return
}