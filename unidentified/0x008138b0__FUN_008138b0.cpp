// FUNC_NAME: SomeManager::constructor
// Address: 0x008138b0
// Role: Constructor for an EARS game manager class, initializes vtable, sub-objects, and callback chain.

void __thiscall SomeManager::constructor(SomeManager* this)
{
    // Set vtable pointer to class-specific vtable
    this->vtablePtr = &PTR_FUN_00d730a0;  // +0x00

    // Initialize two additional pointer slots (likely for type info or static data)
    this->field_0x3C = &PTR_LAB_00d73090;  // +0x3C (offset 0x0F * 4)
    this->field_0x48 = &PTR_LAB_00d7308c;  // +0x48 (offset 0x12 * 4)

    // Initialize sub-object at offset 0x50 (0x14 * 4)
    // The sub-object's constructor is called twice: first FUN_004086d0, then FUN_00408310
    // These likely set up base class vtable and initialize members.
    FUN_004086d0(&this->subObject);  // +0x50, sub-object constructor?
    FUN_00408310(&this->subObject);  // +0x50, subsequent initialization

    // Check if pointer at offset 0x58 is non-null, then call function pointer at offset 0x64
    // This pattern is common for registering a callback or starting a chain.
    if (this->field_0x58 != 0) {
        // Call through function pointer: (*(void (*)(void*))(this->field_0x64))(this->field_0x58)
        typedef void (*CallbackFunc)(void*);
        ((CallbackFunc)(this->field_0x64))(this->field_0x58);  // +0x64 and +0x58
    }

    // Global initialization routine (e.g., singleton instantiation or engine registration)
    FUN_0046c640();
}