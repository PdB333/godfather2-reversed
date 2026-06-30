// FUNC_NAME: EngineObject::finalizeDestroy
void __fastcall EngineObject::finalizeDestroy(EngineObject* this) {
    // Set vtable pointers to derived class tables (possible constructor/destructor pattern)
    this->vtable = &PTR_FUN_00d5c4d8;           // +0x00: most derived vtable
    this->field_0x0C = &PTR_LAB_00d5c4d4;       // +0x0C: second vtable pointer (subobject)

    // Initialize global synchronization objects? (critical sections)
    FUN_00408310(&DAT_01129aa0);                 // initializes a global mutex/CS
    FUN_00408310(&DAT_01129a98);                 // initializes another
    FUN_004086d0(&DAT_012069b4);                 // initializes a global event?
    FUN_004086d0(&DAT_012069c4);                 // initializes another

    // Call a cleanup callback if a subobject pointer is non-null
    if (this->field_0x1C != nullptr) {           // +0x1C: pointer to a subobject
        (this->cleanupCallback)(this->field_0x1C); // +0x28: function pointer for cleanup
    }

    // Change subobject vtable to base class (destructor safety)
    this->field_0x0C = &PTR_LAB_00d5c4d0;       // +0x0C: set to base vtable

    // Clear a global reference count or flag
    DAT_01129814 = 0;                            // global static flag

    // Final shutdown routine (e.g., deinitialize global manager)
    FUN_004083d0();                             // likely destroys global state
}