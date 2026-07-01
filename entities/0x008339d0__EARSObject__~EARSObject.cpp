// FUNC_NAME: EARSObject::~EARSObject
void __thiscall EARSObject::~EARSObject(EARSObject* this)
{
    // Set vtable pointers for base classes (multiple inheritance)
    this->vtable0 = &PTR_FUN_00d73abc;          // +0x00
    this->vtable1 = &PTR_LAB_00d73aac;          // +0x3C (0xf*4)
    this->vtable2 = &PTR_LAB_00d73aa8;          // +0x48 (0x12*4)

    // Check global flag and local flag at +0xC8
    if (DAT_0112db84 != 0 && this->flagC8 == 1) {
        cleanupFunction1(this);                  // FUN_00835380
        this->flagC8 = 0;
    }

    // If flag at +0x9C is set, destroy two sub-objects at +0xCC and +0xD4
    if (this->flag9C == 1) {
        destructSubObject(&this->subObjectCC, 0); // FUN_004089b0
        destructSubObject(&this->subObjectD4, 0); // FUN_004089b0
    }

    // Call destructor function pointers for sub-objects if they exist
    if (this->ptrB0 != 0) {
        (this->funcBC)(this->ptrB0);             // +0xBC function pointer, +0xB0 argument
    }
    if (this->ptrA0 != 0) {
        (this->funcAC)(this->ptrA0);             // +0xAC function pointer, +0xA0 argument
    }
    if (this->ptr50 != 0) {
        (this->func5C)(this->ptr50);             // +0x5C function pointer, +0x50 argument
    }

    // Global cleanup (likely memory manager)
    globalCleanup();                             // FUN_0046c640
}