// FUNC_NAME: FUN_00605960 (likely destructor of an unknown class with subobject management)

// Reconstructed destructor for an unknown class. Sets vtable pointer to destructor vtable,
// then calls Release() on multiple subobjects identified by offsets, calls its own destructor,
// releases an optional resource via stored function pointer, and finally calls global cleanup.

void __fastcall UnknownClass::destructor(UnknownClass *this) {
    // Set vtable to destructor vtable (to prevent virtual calls during destruction).
    this->vtable = &PTR_FUN_00e408cc; // +0x00

    // Cast this+0x0C to a pointer to an object with its own vtable (likely a subobject manager).
    // Call vtable+4 (Release method) with this+0x20 and flag 0.
    (**(code **)(*(int *)this->field_0C + 4))(this->field_20, 0);

    // Repeat for this+0x1C and flag 0.
    (**(code **)(*(int *)this->field_0C + 4))(this->field_1C, 0);

    // Repeat for this+0x18 and flag 0.
    (**(code **)(*(int *)this->field_0C + 4))(this->field_18, 0);

    // Call vtable+0xC (likely the destructor of the subobject manager itself).
    (**(code **)(*(int *)this->field_0C + 0xC))();

    // Release optional resource: if this->field_24 is non-null, call function pointer at this->field_30.
    if (this->field_24 != 0) {
        (*(code *)this->field_30)(this->field_24);
    }

    // Global cleanup (e.g., memory manager or engine shutdown).
    FUN_004083d0();
    return;
}