// FUNC_NAME: EARS::Framework::Object::~Object
void* __thiscall Object::~Object(void* this, byte deletingFlag) {
    // Offset +0x2C: pointer to owned subobject (child)
    void* child = *(void**)((int)this + 0x2C);
    if (child != 0) {
        // Offset +0x38: pointer to child's destructor function
        DestructorFn childDtor = *(DestructorFn*)((int)this + 0x38);
        childDtor(child);
    }

    // Set vtable pointer to base class vtable (prevents virtual calls during destruction)
    *(void**)this = &PTR_FUN_00d5ce9c;

    // Release resource at offset +0x14
    // FUN_0069a0e0 is likely a resource release method
    FUN_0069a0e0(*(void**)((int)this + 0x14));

    if ((deletingFlag & 1) != 0) {
        // Deleting destructor: free memory via operator delete
        FUN_009c8eb0(this);  // operator delete
    }
    return this;
}