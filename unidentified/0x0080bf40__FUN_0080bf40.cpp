// FUNC_NAME: SomeClass::SomeClass
void __thiscall SomeClass::SomeClass(SomeClass *this)
{
    // Set vtable pointer at offset +0x00
    this->vtable = &PTR_FUN_00d72560;
    // Set pointer at offset +0x3C (0x0F * 4)
    *(void**)((char*)this + 0x3C) = &PTR_LAB_00d72550;
    // Set pointer at offset +0x48 (0x12 * 4)
    *(void**)((char*)this + 0x48) = &PTR_LAB_00d7254c;
    // Initialize sub-object at offset +0x50 (0x14 * 4)
    FUN_004086d0((undefined4*)((char*)this + 0x50));
    FUN_00408310((undefined4*)((char*)this + 0x50));
    // Global initialization call
    FUN_0046c640();
}