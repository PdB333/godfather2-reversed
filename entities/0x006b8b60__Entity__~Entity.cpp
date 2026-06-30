// FUNC_NAME: Entity::~Entity
void __thiscall Entity::~Entity(Entity* this) {
    // Set vtable to base class vtable (0x00d5e5e8)
    this->vtable = &PTR_FUN_00d5e5e8;
    // Set function pointers at offsets +0x3C and +0x48 (likely event handlers)
    *(void**)((char*)this + 0x3C) = &PTR_LAB_00d5e5d8;
    *(void**)((char*)this + 0x48) = &PTR_LAB_00d5e5d4;

    // Destroy two embedded sub-objects at offsets +0x50 and +0x58
    // Each sub-object appears to require a two-step cleanup (release then deallocate)
    // First sub-object at +0x50
    FUN_004086d0((char*)this + 0x50); // sub_4086D0 (unknown, likely destructor or decRef)
    FUN_00408310((char*)this + 0x50); // sub_408310 (unknown, likely deallocate or free)
    // Second sub-object at +0x58
    FUN_004086d0((char*)this + 0x58);
    FUN_00408310((char*)this + 0x58);

    // Free dynamically allocated pointer at offset +0x98, if present
    void* allocPtr = *(void**)((char*)this + 0x98);
    if (allocPtr != 0) {
        FUN_009c8eb0(allocPtr); // sub_9C8EB0 (likely operator delete or memory pool deallocation)
        *(void**)((char*)this + 0x98) = 0;
    }

    // Global engine cleanup (e.g., decRef on resource manager)
    FUN_0046c640(); // sub_46C640 (likely platform or memory manager finalize)
}