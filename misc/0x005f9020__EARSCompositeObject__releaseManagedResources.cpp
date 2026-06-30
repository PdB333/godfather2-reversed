// FUNC_NAME: EARSCompositeObject::releaseManagedResources
void EARSCompositeObject::releaseManagedResources(void) {
    // Unknown pre-cleanup call
    FUN_005f9c80();

    // Release the first managed resource (offset +0x18) using its own vtable (index 1) with a reference count of 12
    if (this->field_0x18 != 0) {
        (*(void (__thiscall*)(void*, int))(*(int*)this->field_0x18 + 4))(this->field_0x18, 0xc);
        this->field_0x18 = 0;
    }

    // Release the component pointer (offset +0x14) via the component manager (offset +0x10) using manager's vtable[1]
    if (this->field_0x14 != 0) {
        (*(void (__thiscall*)(void*, int))(*(int*)this->field_0x10 + 4))(this->field_0x14, 0);
        this->field_0x14 = 0;
    }

    // Finalize the component manager via its vtable[3] (no extra arguments)
    (*(void (__thiscall*)(void*))(*(int*)this->field_0x10 + 0xc))();

    // Post-cleanup call
    FUN_005f94d0();
    return;
}