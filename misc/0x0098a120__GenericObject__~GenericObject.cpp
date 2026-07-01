// FUNC_NAME: GenericObject::~GenericObject
void __fastcall GenericObject::~GenericObject(GenericObject* this) {
    // Set vtable to base class vtable (0x00d916a8)
    this->vtable = &PTR_FUN_00d916a8;

    // Release sub-object at offset 0x18 using function pointer at offset 0x24
    if (this->subObj1 != 0) {
        ((void (__stdcall*)(void*))this->subObj1ReleaseFunc)(this->subObj1);
    }

    // Release sub-object at offset 0x04 using function pointer at offset 0x10
    if (this->subObj2 != 0) {
        ((void (__stdcall*)(void*))this->subObj2ReleaseFunc)(this->subObj2);
    }
}