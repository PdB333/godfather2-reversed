// FUNC_NAME: ComponentManager::removeComponent
void __thiscall ComponentManager::removeComponent(uint param_1, int param_2)
{
    uint index = 0;
    uint count = *(uint *)(param_1 + 0x9c); // Number of components (array size)
    if (count != 0) {
        int *componentPtr = (int *)(param_1 + 0x7c); // Beginning of component ID array (or pointer array)
        while (*componentPtr != param_2) {
            index++;
            componentPtr++;
            if (count <= index) {
                // Component not found, directly call cleanup
                FUN_0097d800(param_2);
                return;
            }
        }
        // Found component at 'index'
        if (-1 < (int)index) { // Always true for unsigned < 0x80000000
            FUN_0097d0a0(index); // Remove component at index (shift remaining elements)
        }
    }
    // Cleanup after removal (or if not found)
    FUN_0097d800(param_2);
    return;
}