// FUNC_NAME: ComponentManager::callActiveComponentVirtualMethod
void __fastcall ComponentManager::callActiveComponentVirtualMethod(int thisPtr)
{
    // Active component index stored at offset 0x6C
    int activeIndex = *(int *)(thisPtr + 0x6C);

    // Array of component pointers begins at offset 0x54
    int componentPtr = *(int *)(thisPtr + 0x54 + activeIndex * 4);

    // The component object's vtable is its first 4 bytes.
    // Call the virtual function at vtable offset 0x84 (slot 33).
    void (*func)() = *(void (**)())(*(int *)componentPtr + 0x84);
    func();
}