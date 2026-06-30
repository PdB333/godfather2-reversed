// FUNC_NAME: destructor_for_entity_with_resource
// Function address: 0x006a7240
// Role: Destructor for an object with three vtable slots (multiple inheritance), two inline sub-objects at offsets 0x14 and 0x16, and a resource pointer at offset 0x1c. Contains two-step cleanup for sub-objects and conditional resource deallocation.
void __thiscall destructor_for_entity_with_resource(void)
{
    int *resourcePtr; // Pointer to field at offset 0x1c
    
    resourcePtr = (int *)((char *)this + 0x1c);
    *(void **)this = &PTR_FUN_00d5d810; // Set first vtable (most derived)
    *(void **)((char *)this + 0x3c) = &PTR_LAB_00d5d800; // Set second vtable (base class 2)
    *(void **)((char *)this + 0x48) = &PTR_LAB_00d5d7fc; // Set third vtable (base class 3)
    if ((*resourcePtr != 0) && (*resourcePtr != 0x48)) {
        FUN_006a55f0(resourcePtr); // Cleanup resource if valid and not sentinel
    }
    // Two-step cleanup for sub-object at +0x14
    FUN_004086d0((int *)((char *)this + 0x14));
    FUN_00408310((int *)((char *)this + 0x14));
    // Two-step cleanup for sub-object at +0x16
    FUN_004086d0((int *)((char *)this + 0x16));
    FUN_00408310((int *)((char *)this + 0x16));
    if (*resourcePtr != 0) {
        FUN_004daf90(resourcePtr); // Finalize or deallocate resource
    }
    FUN_0046c640(); // Global cleanup (probably memory manager)
}