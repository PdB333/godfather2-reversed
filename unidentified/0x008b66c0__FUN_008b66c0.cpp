// FUNC_NAME: SomeManager::constructor
void __thiscall SomeManager::constructor(void) {
    // Set vtable pointer
    *(uint32_t *)this = &vtable_SomeManager;

    // Set sub-object vtable pointers (at offsets +0x3C and +0x48)
    *(uint32_t *)((uint8_t *)this + 0x3C) = &vtable_SubObjA;
    *(uint32_t *)((uint8_t *)this + 0x48) = &vtable_SubObjB;

    // Initialize first sub-object (offset +0x50)
    SomeSubObj *subA = (SomeSubObj *)((uint8_t *)this + 0x50);
    subA->construct();   // FUN_004086d0
    subA->initialize();  // FUN_00408310

    // Initialize second sub-object (offset +0x58)
    SomeSubObj *subB = (SomeSubObj *)((uint8_t *)this + 0x58);
    subB->construct();   // FUN_004086d0 (same pattern)
    subB->initialize();  // FUN_00408310

    // Cleanup previous allocation if present (offset +0x8C)
    if (*(uint32_t *)((uint8_t *)this + 0x8C) != 0) {
        FUN_009c8eb0(*(uint32_t *)((uint8_t *)this + 0x8C));  // Destroy/free
        *(uint32_t *)((uint8_t *)this + 0x8C) = 0;
    }

    // Global engine bookkeeping
    FUN_0046c640();
}