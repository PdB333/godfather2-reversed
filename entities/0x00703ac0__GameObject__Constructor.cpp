// FUNC_NAME: GameObject::Constructor
undefined4* __thiscall GameObject::Constructor(undefined4* this, byte flags)
{
    // main vtable for most derived class
    this[0] = &GameObject_vtable; // +0x00

    // interface vtable pointers for multiple inheritance
    this[0xf] = &InterfaceA_vtable;   // +0x3C
    this[0x12] = &InterfaceB_vtable;   // +0x48
    this[0x14] = &InterfaceC_vtable_initial; // +0x50 (will be overridden)

    // construct embedded Name subobject at offset +0x54
    Name::Name((Name*)(this + 0x15));         // +0x54
    Name::Initialize((Name*)(this + 0x15));

    // after Name is initialized, set the correct vtable for InterfaceC
    this[0x14] = &InterfaceC_vtable_final;

    // global object registration (e.g., reference counter, manager)
    ObjectTracker::RegisterObject();

    // if allocation failure flag is set, delete this object (size 0x78)
    if ((flags & 1) != 0) {
        operator delete(this, 0x78);
    }

    return this;
}