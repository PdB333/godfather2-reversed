//FUNC_NAME: Entity::callComponentVirtualFunction
// Address: 0x00842830
// Role: Forwards a call to a virtual function at vtable offset 0x4c on a component object stored at this+0x34.
// The component object's vtable pointer is at component+4.

void __thiscall Entity::callComponentVirtualFunction(undefined4 param2, undefined4 param3, undefined4 param4, undefined4 param5)
{
    // this+0x34: pointer to a component (e.g., state machine, behavior)
    int* componentPtr = *(int**)(this + 0x34);
    // componentPtr+4: vtable pointer of the component
    int* vtable = *(int**)(componentPtr + 4);
    // vtable[0x4c/4] = vtable[19] is the target virtual function
    void (__thiscall *func)(void*, undefined4, undefined4, undefined4, undefined4) = (void (__thiscall*)(void*, undefined4, undefined4, undefined4, undefined4))*(vtable + 0x4c / 4);
    func(componentPtr, param2, param3, param4, param5);
}