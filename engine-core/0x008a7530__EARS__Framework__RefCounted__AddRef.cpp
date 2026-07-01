// FUNC_NAME: EARS::Framework::RefCounted::AddRef
int* EARS::Framework::RefCounted::AddRef() {
    // Call virtual function at vtable index 1 (offset +0x4)
    typedef void (__thiscall *VFunc)(void*);
    VFunc vfunc = reinterpret_cast<VFunc>(*(int*)(*(int*)this + 4));
    vfunc(this);
    return this;
}