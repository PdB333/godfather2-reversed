// FUNC_NAME: CompositeObject::~CompositeObject
// Address: 0x006aa810
// Role: Destructor for a class that owns multiple sub-objects via stored pointers and destructor callbacks.
// +0x00: vtable pointer (set to &PTR_FUN_00d5d9b0)
// +0x04: pointer to sub-object #1, destructor stored at +0x10
// +0x14: pointer to sub-object #2, destructor stored at +0x20
// +0x24: pointer to sub-object #3, destructor stored at +0x30
// +0x34: pointer to sub-object #4, destructor stored at +0x40
// If param_2 & 1, calls FUN_009c8eb0 (likely operator delete) to free memory.

typedef void (__thiscall *DestructorFunc)(void*);

void __thiscall CompositeObject::~CompositeObject(byte freeMemory) {
    // Set vtable to the base class vtable (likely to prevent further virtual dispatch)
    this->vtable = &PTR_FUN_00d5d9b0;

    // Destroy each owned sub-object if it exists
    // Sub-object 4 at +0x34, destructor at +0x40
    if (this->subObject4 != 0) {
        DestructorFunc dtor = (DestructorFunc)(this->destructorFunc4);
        dtor(this->subObject4);
    }

    // Sub-object 3 at +0x24, destructor at +0x30
    if (this->subObject3 != 0) {
        DestructorFunc dtor = (DestructorFunc)(this->destructorFunc3);
        dtor(this->subObject3);
    }

    // Sub-object 2 at +0x14, destructor at +0x20
    if (this->subObject2 != 0) {
        DestructorFunc dtor = (DestructorFunc)(this->destructorFunc2);
        dtor(this->subObject2);
    }

    // Sub-object 1 at +0x04, destructor at +0x10
    if (this->subObject1 != 0) {
        DestructorFunc dtor = (DestructorFunc)(this->destructorFunc1);
        dtor(this->subObject1);
    }

    // Free the object memory if requested
    if (freeMemory & 1) {
        FUN_009c8eb0(this);
    }
}