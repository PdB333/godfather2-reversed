// FUNC_NAME: SomeClass::~SomeClass
void __thiscall SomeClass::~SomeClass(SomeClass* this)
{
    // Set vtable pointer to base class vtable (destructor cleanup)
    this->vtable = &g_vtable_00e444d0;

    // If the member at offset 0xA1C is not null, call its vfunc+0xC (release/destroy)
    Object* subObj = *(Object**)((uint8_t*)this + 0xA1C);
    if (subObj != nullptr) {
        // Virtual function at index 3 (offset 0xC) of subObj's vtable
        (subObj->vtable[3])();
    }

    // Call base/game cleanup function
    FUN_00aa1900();
}