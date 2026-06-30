// FUNC_NAME: ComponentManager::registerComponent
// Address: 0x00564f50
// Role: Registers a component (param2) with the manager. Checks for duplicates (max 4), adds to array, calls virtual method on component, and invokes a callback.

void __thiscall ComponentManager::registerComponent(int this, int component)
{
    uint count;
    int iVar2;
    uint index;
    int *piVar4;
    Callback cb; // size 12? (data, func, reserved)
    uint componentCount;

    // Initialize sub-object at offset 8 in component
    FUN_004d3bc0(component + 8);

    // Query callback for manager at this-4 (likely base class offset)
    iVar2 = FUN_005653d0(this - 4, &cb);

    if (cb.data != 0) {
        cb.func(cb.data);
    }

    // Get current component count from manager's data at iVar2 + 0x10
    componentCount = *(uint *)(iVar2 + 0x10);
    count = 0;
    if (componentCount != 0) {
        do {
            if (*(int *)(iVar2 + count * 4) == component) {
                return; // Already registered
            }
            count++;
        } while (count < componentCount);
    }

    // Add component to list if less than max 4
    if (componentCount < 4) {
        *(int *)(iVar2 + componentCount * 4) = component;
        *(int *)(iVar2 + 0x10) = componentCount + 1;
    }

    // Obtain interface pointer from component at offset 0x110 and call its second virtual method
    piVar4 = (int *)FUN_00564de0(this - 4, component + 0x110);
    (**(void (__thiscall **)(int))(*piVar4 + 4))(component);
}