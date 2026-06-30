// FUNC_NAME: ComponentManager::updateComponent
void __thiscall ComponentManager::updateComponent(void* thisPtr, int someParam) {
    // Process external parameter – likely an input or time delta
    FUN_004d3d90(someParam);

    // Check if internal child component exists (offset +0x8)
    if (*(int**)((char*)thisPtr + 8) != nullptr) {
        // Execute pre‑processing step for the inner component
        FUN_005684b0();

        // Retrieve the inner component object (pointer at +0x8)
        int* innerObject = *(int**)((char*)thisPtr + 8);

        // Call virtual method at vtable index 25 (offset 0x64)
        // This is equivalent to innerObject->someVirtualMethod()
        void (*vtableMethod)(void) = (void (*)(void))(*(int*)(*innerObject + 0x64));
        vtableMethod();
    }
}