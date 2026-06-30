// FUNC_NAME: SimManager::dispatchToComponent
void __thiscall SimManager::dispatchToComponent(int someData)
{
    // Obtain a target component/service via a global getter
    int* component = getSystemComponent(); // FUN_005c3df0

    // Call virtual function at vtable offset 0x18 (e.g., ProcessEvent)
    // First argument: pointer to sub-object at this+0x5 (e.g., inner component)
    // Second argument: someData (event ID or payload)
    ((void (__thiscall*)(void*, int))((int*)(*component))[0x18 / 4])((char*)this + 5, someData);
}