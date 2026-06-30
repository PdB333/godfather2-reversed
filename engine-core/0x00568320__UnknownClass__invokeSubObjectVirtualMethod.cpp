// FUNC_NAME: UnknownClass::invokeSubObjectVirtualMethod
// Function address: 0x00568320
// This member function retrieves a sub-object stored at offset 0x0C and calls
// its 5th virtual method (vtable offset 0x14). Returns the result of that call,
// or 0 if the sub-object pointer is null.
int __thiscall UnknownClass::invokeSubObjectVirtualMethod()
{
    // Get pointer to sub-object at offset +0x0C
    SubObjectType* subObj = *(SubObjectType**)((char*)this + 0x0C);

    // If sub-object exists, call its virtual function at index 5 (vtable+0x14)
    if (subObj != 0) {
        // The sub-object's vtable pointer is at the beginning of the object.
        // Virtual function index 5 corresponds to offset 0x14 in the vtable.
        typedef int (__thiscall* VirtualFunc)(SubObjectType*);
        VirtualFunc func = (VirtualFunc)(subObj->vtable[5]); // vtable[5] is offset 0x14
        return func(subObj);
    }
    return 0;
}