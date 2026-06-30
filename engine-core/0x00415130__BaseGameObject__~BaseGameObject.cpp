// FUNC_NAME: BaseGameObject::~BaseGameObject
void __thiscall BaseGameObject::destructor(BaseGameObject* this) {
    // offset 0x00: vtable pointer
    // First set vtable to the derived-class-specific destructor vtable
    this->vtable = (void*)&PTR_FUN_00e2f720;

    // Release reference-counted child object at offset 0x24
    if (this->field_0x24 != nullptr) {
        // Decrement reference count at child + 0x04
        int* refCount = (int*)((char*)this->field_0x24 + 4);
        *refCount -= 1;
        if (((int*)this->field_0x24)[1] == 0) {
            // Call first virtual function (likely destructor) on child
            ((void(__thiscall*)(void*))(*((void**)this->field_0x24)[0]))(this->field_0x24);
        }
        this->field_0x24 = nullptr;
    }

    // Clear weak pointer to another object at offset 0x20
    if (this->field_0x20 != nullptr) {
        // Nullify the back-reference at child + 0x08
        *(uint32_t*)((char*)this->field_0x20 + 8) = 0;
        this->field_0x20 = nullptr;
    }

    // Switch vtable to intermediate base class destructor vtable
    this->vtable = (void*)&PTR_FUN_00e353e0;

    // Release member object at offset 0x0C
    if (this->field_0x0C != nullptr) {
        FUN_004a6400();  // Possibly release or decrement reference count
    }
    if (this->field_0x0C != nullptr) {
        // Call virtual destructor on member object with deletion flag 1
        ((void(__thiscall*)(void*, uint32_t))(*((void**)this->field_0x0C)[0]))(this->field_0x0C, 1);
    }

    // Finally set vtable to the root base class vtable
    this->vtable = (void*)&PTR_LAB_00e2f638;
}