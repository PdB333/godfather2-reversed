//FUNC_NAME: SystemManager::SystemManager
void __fastcall SystemManager::SystemManager(SystemManager* this)
{
    // Set vtable pointers for the main object and embedded subobjects
    this->vtable = &PTR_FUN_00d778a0;                     // +0x00: main vtable
    this->subObject1 = &PTR_LAB_00d77894;                 // +0x0C: subobject vtable (offset 3)
    this->subObject2 = &PTR_LAB_00d77884;                 // +0x14: subobject vtable (offset 5)
    this->subObject3 = &PTR_LAB_00d77880;                 // +0x18: subobject vtable (offset 6)

    // Initialize global singletons / systems
    initSingleton(&g_singleton1);                         // DAT_0112fe38
    initSingleton(&g_singleton2);                         // DAT_0112fe10
    registerClass(&g_classRegistry1);                     // DAT_0112e308
    initSingleton(&g_singleton3);                         // DAT_0112e300
    registerClass(&g_classRegistry1);                     // DAT_0112e300 (reused)
    initSingleton(&g_singleton4);                         // DAT_0112e2f8
    registerClass(&g_classRegistry2);                     // DAT_0112e2f8

    // Call a virtual method on an embedded object at offset +0x28 (param_1[10])
    // The method is at vtable offset 0x0C (4th virtual function)
    (this->embeddedObject->vtable[3])();                  // (**(code **)(*(int *)this->embeddedObject + 0xc))();

    // Register a hash (likely for event or resource)
    registerHash(0x23aea276);                             // FUN_004639e0

    // Check a flag at offset +0x34 (byte at param_1 + 0x0D)
    if ((this->flags & 1) != 0) {
        // Call a virtual method on another embedded object at offset +0x30 (param_1[0x0C])
        // with argument 0, then set it to null
        this->embeddedObject2->vtable[1](this->embeddedObject2, 0); // (**(code **)(*(int *)this->embeddedObject2 + 4))(this->embeddedObject2,0);
        this->embeddedObject2 = nullptr;                  // param_1[0x0C] = 0
    }

    // Free dynamically allocated subobjects if they exist
    if (this->ptr1 != nullptr) {                          // param_1[0x12] at offset +0x48
        operatorDelete(this->ptr1);                       // FUN_009c8f10
    }
    if (this->ptr2 != nullptr) {                          // param_1[0x0E] at offset +0x38
        destructSubObject(&this->ptr2);                   // FUN_004daf90 (takes address of pointer)
    }
    if (this->ptr3 != nullptr) {                          // param_1[7] at offset +0x1C
        operatorDelete(this->ptr3);                       // FUN_009c8f10
    }

    // Reassign vtable pointers for subobjects (possibly re-initialization)
    this->subObject3 = &PTR_LAB_00d7782c;                 // +0x18: new vtable
    g_globalFlag = 0;                                     // DAT_01129884 = 0
    this->subObject2 = &PTR_LAB_00e30fe0;                 // +0x14: new vtable

    // Final initialization steps
    finalizeInit1();                                      // FUN_0049c640
    finalizeInit2();                                      // FUN_004083d0
}