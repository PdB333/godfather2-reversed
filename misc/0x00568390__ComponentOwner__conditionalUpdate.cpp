// FUNC_NAME: ComponentOwner::conditionalUpdate
void __thiscall ComponentOwner::conditionalUpdate(int thisPtr) {
    // this+0x34: pointer to a component object (likely a derived class)
    int* component = *(int**)(thisPtr + 0x34);
    if (component == nullptr) {
        return;
    }
    // Virtual call at vtable+0x20: probably isActive() or shouldUpdate()
    bool shouldUpdate = (*(bool (__thiscall**)(int*))(*(int*)component + 0x20))(component);
    if (!shouldUpdate) {
        // Virtual call at vtable+0x18: actual update method
        (*(void (__thiscall**)(int*))(*(int*)component + 0x18))(component);
    }
    return;
}