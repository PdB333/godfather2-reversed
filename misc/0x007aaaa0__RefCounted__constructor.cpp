// FUNC_NAME: RefCounted::constructor

class RefCounted {
public:
    void* vtable; // +0x00: pointer to virtual function table
    int refCount; // +0x04: reference count, initially 0

    __thiscall void constructor() {
        this->vtable = (void*)&PTR_LAB_00d6ba68; // set vtable to global table pointer
        this->refCount = 0;                      // initialize reference count
    }
};