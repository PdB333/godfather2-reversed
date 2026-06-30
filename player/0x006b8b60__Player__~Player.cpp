// FUNC_NAME: Player::~Player
// Function address: 0x006b8b60
// Destructor for Player class. Sets vtables to special destructor vtables,
// destroys embedded sub-objects, deletes dynamically allocated member, then calls global cleanup.

void __thiscall Player::~Player(Player* this) {
    // Set vtable pointers to special destructor vtables to prevent virtual calls during destruction
    this->vtable = &PTR_FUN_00d5e5e8;          // +0x00: main vtable
    this->vtable2 = &PTR_LAB_00d5e5d8;         // +0x3C: secondary vtable (base class 1)
    this->vtable3 = &PTR_LAB_00d5e5d4;         // +0x48: tertiary vtable (base class 2)

    // Destroy sub-object at offset 0x50 (param_1 + 0x14)
    FUN_004086d0(&this->subObject1);           // +0x50: sub-object 1 destructor (first step)
    FUN_00408310(&this->subObject1);           // +0x50: sub-object 1 destructor (second step)

    // Destroy sub-object at offset 0x58 (param_1 + 0x16)
    FUN_004086d0(&this->subObject2);           // +0x58: sub-object 2 destructor (first step)
    FUN_00408310(&this->subObject2);           // +0x58: sub-object 2 destructor (second step)

    // Delete dynamically allocated member at offset 0x98 (param_1[0x26])
    if (this->m_pSomePointer != nullptr) {
        FUN_009c8eb0(this->m_pSomePointer);    // +0x98: destructor for dynamically allocated object
        this->m_pSomePointer = nullptr;
    }

    // Global cleanup function (likely memory manager or static destructor)
    FUN_0046c640();
}