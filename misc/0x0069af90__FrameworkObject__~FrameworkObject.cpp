// FUNC_NAME: FrameworkObject::~FrameworkObject
void __thiscall FrameworkObject::~FrameworkObject(FrameworkObject *this)
{
    // +0x2C: pointer to resource data
    void *resource = *(void **)((uint8_t *)this + 0x2C);
    if (resource != 0) {
        // +0x38: function pointer to release/deleter for the resource
        void (*releaseFunc)(void *) = *(void (**)(void *))((uint8_t *)this + 0x38);
        releaseFunc(resource);
    }
    // Set vtable to base class vtable
    *(int **)this = &PTR_FUN_00d5ce9c;
    // Destroy subobject at +0x14 (e.g., member object or another base)
    FUN_0069a0e0(*(void **)((uint8_t *)this + 0x14));
}