// FUNC_NAME: GameManager::~GameManager
// Destructor for a manager/subsystem class at 0x007521f0
// Sets vtable, cleans up subresources, and calls global shutdown.
void __thiscall GameManager::~GameManager(GameManager* this) {
    // Set vtable to the final destructor vtable (likely base class)
    *this->vtable = &PTR_LAB_00d64b08; // +0x00

    // Internal destructor / base destructor
    FUN_00751ec0();

    // Check bit 5 (0x20) of flags at +0xCC
    if (((uint)this->field_0xCC >> 5 & 1) != 0) {
        // Shutdown some subsystem (0,0 params)
        FUN_007f9340(0, 0);
        // Clear the bit
        this->field_0xCC &= 0xFFFFFFDF;
    }

    // Free sub‑objects stored at various offsets
    if (this->ptrAt0x98 != 0) {   // +0x98
        FUN_004daf90(this->ptrAt0x98);   // operator delete
    }
    if (this->ptrAt0x88 != 0) {   // +0x88
        FUN_004daf90(this->ptrAt0x88);
    }
    if (this->ptrAt0x7C != 0) {   // +0x7C
        FUN_004daf90(this->ptrAt0x7C);
    }
    if (this->ptrAt0x6C != 0) {   // +0x6C
        FUN_004daf90(this->ptrAt0x6C);
    }
    if (this->ptrAt0x60 != 0) {   // +0x60
        FUN_004daf90(this->ptrAt0x60);
    }

    // Final global cleanup
    FUN_0080ea60();
}