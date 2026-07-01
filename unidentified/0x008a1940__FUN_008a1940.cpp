// FUNC_NAME: UnknownClass::setStateToSevenAndCallVirtual
void __fastcall UnknownClass::setStateToSevenAndCallVirtual(UnknownClass* this) {
    // Set member at offset 0x1c to 7 (likely an enum for state or type)
    *(int*)((char*)this + 0x1c) = 7;

    // Call virtual function at vtable offset 0x90 on the subobject at offset 0xc
    // The subobject is passed a pointer to a field at offset 0x230 as its 'this' pointer
    void* subObject = *(void**)((char*)this + 0xc);
    void (*virtualFunc)(void*) = *(void(**)(void*))((*(int*)subObject) + 0x90);
    virtualFunc((char*)this + 0x230);
}