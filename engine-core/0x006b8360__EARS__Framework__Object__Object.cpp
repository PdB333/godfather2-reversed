// FUNC_NAME: EARS::Framework::Object::Object
void __fastcall Object::constructor(Object *this)
{
    // Set vtable pointer to this class's vtable
    this->vtable = (VTable *)&PTR_FUN_00d5e5b8;

    // Set function pointers at offsets +0x3C and +0x48
    // These likely point to virtual method overrides or callbacks
    *(void **)((char *)this + 0x3C) = &PTR_LAB_00d5e5a8;
    *(void **)((char *)this + 0x48) = &PTR_LAB_00d5e5a4;

    // Construct sub-object at offset +0x50 (size unknown)
    FUN_004086d0((Object *)((char *)this + 0x50));  // Sub-object constructor
    FUN_00408310((Object *)((char *)this + 0x50));  // Sub-object post-initialization

    // Global module initialization (singleton setup or static ctor)
    FUN_0046c640();
}