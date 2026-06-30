// FUNC_NAME: Player::Player
// Constructor for Player class (EARS::Game::Player)
// Initializes multiple base class vtables and performs setup

class Player {
public:
    // +0x00: primary vtable pointer
    // +0x3C: base class 1 vtable pointer
    // +0x48: base class 2 vtable pointer
    // +0x50: base class 3 vtable pointer
    // +0x64: some pointer member
    // +0x98: another pointer member

    Player();
};

// External functions
void BaseClass_Constructor(Player* thisPtr);            // FUN_006e9760
void SomeGlobalFunction(uint32_t* ptr);                 // FUN_004086d0
void ReleaseMember(void* memberPtr);                     // FUN_004daf90
void PostInitFunction();                                // FUN_0046c640

// External vtable references
extern void* Player_vtable;              // PTR_FUN_00d5fcd8
extern void* Base1_vtable;               // PTR_LAB_00d5fcc8
extern void* Base2_vtable;               // PTR_LAB_00d5fcc4
extern void* Base3_vtable;               // PTR_LAB_00d5fcc0
extern void* Base3_Alt_vtable;           // PTR_LAB_00e32854

void Player::Player() {
    // Set primary vtable
    this->base_vtable = &Player_vtable;          // +0x00

    // Set base class vtables
    *(void**)((char*)this + 0x3C) = &Base1_vtable;   // +0x3C
    *(void**)((char*)this + 0x48) = &Base2_vtable;   // +0x48
    *(void**)((char*)this + 0x50) = &Base3_vtable;   // +0x50

    // Call base class constructor
    BaseClass_Constructor(this);                     // FUN_006e9760

    // Global initialization (e.g., reference counting)
    SomeGlobalFunction(&DAT_0120e93c);               // FUN_004086d0

    // Release existing members if they were allocated (reuse from pool)
    void** memberAt98 = (void**)((char*)this + 0x98);
    if (*memberAt98 != nullptr) {
        ReleaseMember(memberAt98);                   // FUN_004daf90
    }

    void** memberAt64 = (void**)((char*)this + 0x64);
    if (*memberAt64 != nullptr) {
        ReleaseMember(memberAt64);                   // FUN_004daf90
    }

    // Update base class 3 vtable (possibly for further derivation)
    *(void**)((char*)this + 0x50) = &Base3_Alt_vtable;

    // Post-initialization
    PostInitFunction();                              // FUN_0046c640
}