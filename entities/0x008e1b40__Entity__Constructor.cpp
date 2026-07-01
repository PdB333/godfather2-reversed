// FUNC_NAME: Entity::Constructor
void __thiscall Entity::Constructor(Entity* thisPtr) {
    // Set base class vtable pointers (multiple inheritance)
    thisPtr->vtable0 = &PTR_FUN_00d80248;                      // +0x00
    *(void***)((char*)thisPtr + 0x3C) = &PTR_LAB_00d80238;     // +0x3C (index 0xF)
    *(void***)((char*)thisPtr + 0x48) = &PTR_LAB_00d80234;     // +0x48 (index 0x12)
    *(void***)((char*)thisPtr + 0x50) = &PTR_LAB_00d80230;     // +0x50 (index 0x14)
    *(void***)((char*)thisPtr + 0x54) = &PTR_LAB_00d801d0;     // +0x54 (index 0x15)
    *(void***)((char*)thisPtr + 0x58) = &PTR_LAB_00d80168;     // +0x58 (index 0x16)

    // If the inner object pointer at offset 0x190 (400) is not null, destroy it first
    EntityInnerObject* innerObj = *(EntityInnerObject**)((char*)thisPtr + 0x190);
    if (innerObj != nullptr) {
        EntityInnerObject::Destructor(innerObj);               // FUN_004daf90
    }

    // Set final (derived class) vtable pointers
    thisPtr->vtable0 = &PTR_FUN_00d80008;
    *(void***)((char*)thisPtr + 0x3C) = &PTR_LAB_00d7fff8;
    *(void***)((char*)thisPtr + 0x48) = &PTR_LAB_00d7fff4;
    *(void***)((char*)thisPtr + 0x50) = &PTR_LAB_00d7fff0;
    *(void***)((char*)thisPtr + 0x54) = &PTR_LAB_00d7ff90;
    *(void***)((char*)thisPtr + 0x58) = &PTR_LAB_00d7ff28;

    // Call base class initialization
    Entity::BaseInitialize();                                  // FUN_0046ea20
}