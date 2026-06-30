// FUNC_NAME: Entity::~Entity
void __fastcall Entity::_destructor(Entity *this)
{
    // +0x00: vtable pointer, +0x04: RTTI/class info, +0x30: sub-object pointer
    Entity *subObject = *(Entity **)((char *)this + 0x30);
    // Set vtable to derived class (current class)
    *(void **)this = &PTR_FUN_00e39ff4;
    *(int *)((char *)this + 4) = &PTR_LAB_00e3a018;
    if (subObject)
    {
        // Destroy sub-object (likely own destructor + free)
        FUN_00559ca0(subObject);
        FUN_009c8eb0(subObject);
    }
    // Switch vtable to base class (after derived cleanup)
    *(void **)this = &PTR_LAB_00d987cc;
    *(int *)((char *)this + 4) = &PTR_LAB_00d96914;
}