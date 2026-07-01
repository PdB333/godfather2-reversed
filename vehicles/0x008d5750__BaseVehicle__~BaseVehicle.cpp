// FUNC_NAME: BaseVehicle::~BaseVehicle

void __thiscall BaseVehicle::destroy(BaseVehicle *this) {
    // Set vtable pointer to the destructor vtable for this class
    this->vfptr = (void **)&PTR_FUN_00d7d66c;

    // Initialize vtable pointers of sub-objects at offsets 0x3C and 0x48
    *(void **)((char *)this + 0x3C) = &PTR_LAB_00d7d65c; // +0x3C: sub-object vtable
    *(void **)((char *)this + 0x48) = &PTR_LAB_00d7d658; // +0x48: sub-object vtable

    // If the pointer at offset 0x64 is valid, call its first vtable entry with argument 1
    // (likely a custom destructor or release function for a component)
    if (*(void **)((char *)this + 0x64) != nullptr) {
        void *component = *(void **)((char *)this + 0x64);
        void **vtable = *(void ***)component;
        ((void (__thiscall *)(void *, int))vtable[0])(component, 1);
    }

    // Release a global synchronization object (likely a mutex or semaphore)
    release(&DAT_0120e93c);

    // Release and clear two sub-objects at offsets 0x50 and 0x58 (e.g., physics body, graphics object)
    release((void *)((char *)this + 0x50));
    clear((void *)((char *)this + 0x50));
    release((void *)((char *)this + 0x58));
    clear((void *)((char *)this + 0x58));

    // If pointer at 0x7C is valid, call function pointed by vtable at 0x88
    if (*(void **)((char *)this + 0x7C) != nullptr) {
        void *comp = *(void **)((char *)this + 0x7C);
        void **vt = *(void ***)((char *)this + 0x88);
        ((void (__thiscall *)(void *))vt)(comp);
    }

    // If pointer at 0x6C is valid, call function pointed by vtable at 0x78
    if (*(void **)((char *)this + 0x6C) != nullptr) {
        void *comp = *(void **)((char *)this + 0x6C);
        void **vt = *(void ***)((char *)this + 0x78);
        ((void (__thiscall *)(void *))vt)(comp);
    }

    // Final cleanup call (e.g., global reference decrement or notification)
    FUN_0046c640();
}