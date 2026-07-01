// FUNC_NAME: Player::Player
// Constructor for Player class at 0x0089cfe0
// Initializes vtable pointers, fields, and calls base class constructors

class Player {
public:
    // Vtable pointer at +0x00
    void* vtable;
    // +0x04: Active flag (set to 1)
    int m_active;
    // +0x08: Some state (set to 0)
    int m_state;
    // +0x0C: Interface vtable pointer (set to &PTR_LAB_00d78620)
    void* ifaceVtable1;
    // +0x10: (skipped)
    // +0x14: (skipped)
    // +0x18: (skipped)
    // +0x1C: Another interface vtable pointer (set to &PTR_LAB_00d78618)
    void* ifaceVtable2;
    // +0x20: Some pointer (set to 0)
    void* m_pointer;
    // +0x24: Hash/ID (set to 0xfe16702f)
    unsigned int m_hash;
    // +0x28: (set to 0)
    int m_field28;
    // +0x2C: (set to 0)
    int m_field2C;
    // +0x30: (set to 0)
    int m_field30;
    // +0x34: (set to 0)
    int m_field34;
    // +0x38: Global data pointer (set from _DAT_00d5780c)
    void* m_globalData;
    // +0x3C: Parameter 2 (passed to constructor)
    int m_param2;
    // +0x40: Parameter 3 (passed to constructor)
    int m_param3;
    // +0x44: (skipped)
    // +0x48: Byte flag (set to 0)
    char m_byteFlag;

    Player(int param2, int param3) {
        // Set initial vtable (base class)
        this->vtable = &PTR_FUN_00e2f19c;
        this->m_active = 1;
        this->m_state = 0;

        // Call base class constructor (FUN_004814b0)
        FUN_004814b0();

        // Set interface vtables
        this->ifaceVtable2 = &PTR_FUN_00e32808;
        this->m_pointer = 0;

        // Override vtable to derived class
        this->vtable = &PTR_FUN_00d78684;
        this->ifaceVtable1 = &PTR_LAB_00d78620;
        this->ifaceVtable2 = &PTR_LAB_00d78618;

        // Initialize fields
        this->m_hash = 0xfe16702f;
        this->m_field28 = 0;
        this->m_field2C = 0;
        this->m_field30 = 0;
        this->m_field34 = 0;
        this->m_globalData = _DAT_00d5780c;
        this->m_param3 = param3;
        this->m_param2 = param2;
        this->m_byteFlag = 0;

        // Call global initializer (FUN_00408680)
        FUN_00408680(&DAT_012069c4);

        // Call another base class constructor (FUN_00481530)
        FUN_00481530();
    }
};