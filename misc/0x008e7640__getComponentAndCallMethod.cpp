// FUNC_NAME: getComponentAndCallMethod
// Address: 0x008e7640
// Role: Retrieves a component interface from the object and calls a method on it, returning the result.
// The object's vtable at offset 0xc provides a method to obtain a component pointer.
// That component's vtable at offset 8 is the method to invoke.

int __thiscall getComponentAndCallMethod(void* thisPtr)
{
    int result;
    void* component;

    result = getGlobalManager(); // FUN_0042b400 - likely returns a singleton manager
    component = (*(void* (__thiscall**)(void*))(*(int*)thisPtr + 0xc))(thisPtr); // virtual call at vtable+0xc
    if (component != nullptr) {
        result = (*(int (__thiscall**)(void*))(*(int*)component + 8))(component); // virtual call at vtable+8
    }
    return result;
}