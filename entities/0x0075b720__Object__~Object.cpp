// FUNC_NAME: Object::~Object
void __thiscall Object::~Object(Object* this) {
    int* somePtr; // piVar1, derived from this+0x98 + 0x1e90
    uint* current; // puVar3, linked list node

    // Set vtable pointers (likely for destruction chaining)
    this[0].vtable = &PTR_LAB_00d6515c; // offset 0x00
    this[5].vtable2 = &PTR_LAB_00d65158; // offset 0x14 (param_1[0x14])

    somePtr = (int*)(this[0x26].someData + 0x1e90); // +0x98 + 0x1e90 (0x2028 from base)

    // Condition to free a resource
    if ((*somePtr == this[0x27].somePointer) && ((this[0x20].flags >> 7 & 1) != 0) && (*somePtr != 0)) {
        FUN_004daf90(somePtr); // free resource
        *somePtr = 0;
    }

    // Free non-null members at various offsets
    if (this[0x32].member != 0) { // +0xC8
        FUN_004daf90(&this[0x32]);
    }
    if (this[0x30].member != 0) { // +0xC0
        FUN_004daf90(&this[0x30]);
    }
    if (this[0x2e].member != 0) { // +0xB8
        FUN_004daf90(&this[0x2e]);
    }
    if (this[0x2b].member != 0) { // +0xAC
        FUN_004daf90(&this[0x2b]);
    }
    if (this[0x29].member != 0) { // +0xA4
        FUN_004daf90(&this[0x29]);
    }
    if (this[0x27].member != 0) { // +0x9C
        FUN_004daf90(&this[0x27]);
    }

    // Switch to base class vtable (for destruction)
    this[0x14].vtable = &PTR_FUN_00e32808; // offset 0x50

    // Detach all nodes in the linked list starting at this[0x15] (offset 0x54)
    current = (uint*)this[0x15].listHead; // offset 0x54
    while (current != (uint*)0x0) {
        uint* next = (uint*)current[1]; // next pointer (offset 0x04 in node)
        current[1] = 0; // clear next
        current[0] = 0; // clear prev/data? (offset 0x00 in node)
        current = next;
    }

    // Global cleanup call
    FUN_004ac1e0();
}