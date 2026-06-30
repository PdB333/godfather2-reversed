// FUNC_NAME: Entity::getComponentByHash
// Function at 0x006e46c0: Retrieves a component by a hash (0x369ac561) and writes the hash into the component's first field.
// The hash is assumed to be a unique identifier for a component type (e.g., kComponent_Crew).
// Offset 0x100 in 'this' points to a component manager (likely an array or manager object).
// The virtual function at manager->vtable[0x10] is called with hash and an out-pointer.
// It returns non-zero if component exists, then writes the hash into the component (to mark it?).
// Unreachable block warning indicates possible control flow simplification.

void __thiscall Entity::getComponentByHash(Entity* thisPtr)
{
    // 'thisPtr' is the Entity object; offset 0x100 holds a pointer to a ComponentManager
    ComponentManager** managerPtr = (ComponentManager**)((char*)thisPtr + 0x100);
    ComponentManager* manager = *managerPtr;

    // Hash constant representing a specific component type (e.g., CrewComponent)
    uint componentHash = 0x369ac561;

    // Output pointer to receive the found component
    Component* component = nullptr;

    // Call virtual function at offset 0x10 on the component manager.
    // Typical signature: bool ComponentManager::getComponent(uint hash, Component** out);
    bool found = (manager->vtable[0x10])(componentHash, &component);

    // Whether found or not, write the hash into the component's first field.
    // This may serve as a type check or flag.
    *component = (Component)componentHash;

    // Note: The original code had identical assignments in both branches.
    // The check for 'found' is effectively dead code but preserved for accuracy.
    return;
}