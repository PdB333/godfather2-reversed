// FUNC_NAME: InterfaceWrapper::initialize
void __thiscall InterfaceWrapper::initialize(void **this, void *interfacePtr, int childParam)
{
    // Store the interface pointer (likely a vtable pointer or COM-like interface)
    *this = interfacePtr;

    // Call a virtual function at offset 8 (e.g., AddRef, Initialize, etc.)
    (*(void (__thiscall **)(void *))(*(int *)interfacePtr + 8))(interfacePtr);

    // If childParam is non-zero, create a child object via factory function
    if (childParam != 0) {
        this[1] = (void *)FUN_004265d0(childParam, *this);
    } else {
        this[1] = 0;
    }
}