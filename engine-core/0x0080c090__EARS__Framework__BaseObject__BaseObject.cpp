// FUNC_NAME: EARS::Framework::BaseObject::BaseObject
EARS::Framework::BaseObject* __thiscall EARS::Framework::BaseObject::BaseObject(EARS::Framework::BaseObject* this, byte flags)
{
    // Set primary vtable pointer (offset 0x00)
    this->vtable = (void*)0x00d72560;
    // Set secondary interface vtable at offset 0x3C (15*4)
    *(void**)((uintptr_t)this + 0x3C) = (void*)0x00d72550;
    // Set tertiary interface vtable at offset 0x48 (18*4)
    *(void**)((uintptr_t)this + 0x48) = (void*)0x00d7254c;
    // Initialize embedded sub-object at offset 0x14 (5*4)
    // Likely a base class or component like Node/Component
    FUN_004086d0((undefined4*)((uintptr_t)this + 0x14));
    FUN_00408310((undefined4*)((uintptr_t)this + 0x14));
    // Global state initialization (singleton, manager, etc.)
    FUN_0046c640();
    // If flags low bit set, call custom operator delete with size 0x6c (108 bytes)
    // This handles memory deallocation for objects allocated via placement new
    if ((flags & 1) != 0) {
        FUN_0043b960(this, 0x6c);
    }
    return this;
}