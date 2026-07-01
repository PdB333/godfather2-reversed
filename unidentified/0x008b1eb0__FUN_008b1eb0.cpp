// FUNC_NAME: SomeManager::~SomeManager
void __thiscall SomeManager::~SomeManager(SomeManager* this) {
    // Set vtable to current class vtable (safety)
    this->vtable = &PTR_FUN_00d7abfc;
    this->field_4 = &PTR_LAB_00d7abec;

    // Destroy static objects (singletons)
    destroyStaticObject(&g_staticObject1);  // DAT_01206778
    destroyStaticObject(&g_staticObject2);  // DAT_01206760

    // Set vtable for sub-object at offset 0x1c (param_1[7])
    this->subObject.vtable = &PTR_FUN_00d7ab88;
    destroySubObject(&this->subObject);  // FUN_008b1cf0

    // Release pointer at offset 0x2c (param_1[0xb])
    if (this->field_0x2c != 0) {
        releaseObject(this->field_0x2c);  // FUN_009c8f10
    }

    // Global cleanup
    globalCleanup();  // FUN_00481520

    // Release pointer at offset 0x10 (param_1[4])
    if (this->field_0x10 != 0) {
        releaseObject(this->field_0x10);  // FUN_009c8f10
    }

    // Another global cleanup
    globalCleanup2();  // FUN_004083d0

    // Set vtable to base class vtable before base destructor
    this->vtable = &PTR_LAB_00d7ab80;

    // Mark manager as destroyed
    g_managerInitialized = 0;  // DAT_0112988c
}