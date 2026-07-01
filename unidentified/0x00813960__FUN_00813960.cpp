//FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(SomeClass* this) {
    // Set vtable pointers to destructor vtables (likely to prevent further virtual calls)
    this->vtable = &PTR_FUN_00d73070;          // +0x00: main vtable
    this->field_0x3c = &PTR_LAB_00d73060;      // +0x3c: secondary vtable or data
    this->field_0x48 = &PTR_LAB_00d7305c;      // +0x48: another vtable or data

    // Destroy sub-object at offset 0x50 (size unknown)
    FUN_004086d0(&this->subObject);            // +0x50: sub-object destructor call 1
    FUN_00408310(&this->subObject);            // +0x50: sub-object destructor call 2

    // Destroy another sub-object at offset 0x58 (size unknown)
    FUN_00408310(&this->subObject2);           // +0x58: second sub-object destructor

    // Unregister a pointer if present (e.g., from a list)
    if (this->ptrAt0x74 != 0) {                // +0x74: pointer to some resource
        FUN_004035f0(this->ptrAt0x74, 0x16, &this->field_0x3c); // unregister with type 0x16
        this->ptrAt0x74 = 0;                   // clear pointer
    }

    // Delete another pointer using a function pointer stored in the object
    if (this->ptrAt0x60 != 0) {                // +0x60: another pointer
        (this->deleteFunc)(this->ptrAt0x60);   // +0x6c: function pointer (likely a custom deleter)
    }

    // Global cleanup (e.g., memory manager flush)
    FUN_0046c640();
}