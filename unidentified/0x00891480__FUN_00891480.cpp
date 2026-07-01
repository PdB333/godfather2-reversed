// FUNC_NAME: UnknownClass::constructor
void __thiscall UnknownClass::constructor(UnknownClass* this) // 0x00891480
{
    // Set primary vtable
    this->vtable = &PTR_FUN_00d77790; // +0x00
    // Set additional virtual table pointers (possibly interface vtables or substates)
    this->vtable2 = &PTR_LAB_00d77780; // +0x3C (offset 0xF * 4)
    this->vtable3 = &PTR_LAB_00d7777c; // +0x48 (offset 0x12 * 4)
    this->vtable4 = &PTR_LAB_00d77778; // +0x50 (offset 0x14 * 4) (will be overwritten later)

    // Call base class constructor (likely initializes common fields)
    baseClassConstructor(this); // FUN_00891df0

    // Initialize five sub‑objects at offsets 0x54, 0x5C, 0x64, 0x6C, 0x74 (each 8 bytes)
    for (int i = 0; i < 5; i++) {
        SubObject* sub = reinterpret_cast<SubObject*>(&this->pad0x54[i * 8]);
        subObjectInit(sub); // FUN_004086d0 (sub‑object placement new / first‑stage init)
        subObjectConstruct(sub); // FUN_00408310 (second‑stage constructor)
    }

    // Override the vtable4 pointer (likely switching to a different interface)
    this->vtable4 = &PTR_LAB_00e32854; // +0x50 overwritten

    // Global initialisation hook (e.g. register self with manager)
    globalInitFunction(); // FUN_0046c640
}