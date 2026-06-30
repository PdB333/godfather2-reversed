// FUNC_NAME: ObjectHandle::callVirtualMethodIndex8
// Function address: 0x004184a0
// Role: Calls a virtual function at vtable offset 0x20 (index 8) on an object whose pointer is stored at this+4.
// This is a thunk used to dispatch a method call through an interface handle (likely a COM-like object wrapper).

class ObjectHandle {
public:
    // Calls the virtual function at index 8 (offset 0x20) on the referenced object.
    void __thiscall callVirtualMethodIndex8(void) {
        // Retrieve the actual object's vtable pointer from offset 4 of this handle.
        // Then call the function at vtable offset 0x20 (8th entry).
        (**(void (__thiscall**)(void))(*((int*)this + 1) + 0x20))();
    }
};