// FUNC_NAME: GameObject::~GameObject

// Destructor for a game object with multiple base classes (4 vtable pointers at offsets 0x00, 0x3C, 0x48, 0x50).
// Deallocates two dynamically allocated members at offsets +0x78 and +0x80, then performs global cleanup.
// 0x006cc2a0

void __fastcall GameObject::~GameObject(GameObject* this) {
    // Set vtable pointers to base class vtables for proper virtual call during destruction
    this->vtable = &VTABLE_GameObject;           // +0x00 primary vtable
    *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x3C) = &VTABLE_Base1; // +0x3C
    *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x48) = &VTABLE_Base2; // +0x48
    *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x50) = &VTABLE_Base3; // +0x50

    // Free dynamically allocated memory if present (members at offsets +0x78 and +0x80)
    if (this->memberAt0x78 != nullptr) { // +0x78
        freePointer(&this->memberAt0x78); // FUN_004daf90: frees memory and sets pointer to null
    }
    if (this->memberAt0x80 != nullptr) { // +0x80
        freePointer(&this->memberAt0x80); // FUN_004daf90
    }

    // Final cleanup (likely memory deallocation or global destructor chain)
    globalDestructorEpilogue(); // FUN_00473880
}