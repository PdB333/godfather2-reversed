// FUNC_NAME: ComponentManager::getComponentData
// Address: 0x0054a660
// This function looks up a component by a fixed hash (0x33a16735) and returns data at offset 0x14 from it.
// The hash likely identifies a specific component type or instance within the manager.

__thiscall void* ComponentManager::getComponentData(ComponentManager* this)
{
    // Calls internal lookup function with a 32-bit hash constant.
    // FUN_004b9ca0 is likely a member or global function that finds an object by hash.
    // Parameter order: (this, hash) for __thiscall, or possibly (param1, hash) for thiscall with explicit this.
    // Since the original decompiled code uses param_1 directly for both arguments, 
    // we treat 'this' as the first argument to the lookup.
    int foundObject = FUN_004b9ca0(this, 0x33a16735);
    if (foundObject != 0) {
        // Return the value at offset 0x14 from the found object.
        // This offset likely stores a pointer or handle to the component's data.
        return *(void**)(foundObject + 0x14);
    }
    return 0;
}