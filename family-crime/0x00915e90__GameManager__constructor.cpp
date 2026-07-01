// FUNC_NAME: GameManager::constructor

// 0x00915e90 — Constructor for the game manager singleton.
// Initializes base class, sets vtable pointers, and initializes fields to zero.

class GameManager : public BaseManager {
public:
    // Base class constructor call at 0x00957ed0
    void __thiscall constructor() {
        // Call base class constructor
        FUN_00957ed0(this);  // BaseManager::constructor (unknown)

        // Set vtable pointers for this class (multiple inheritance?)
        // Offset +0x50: first interface vtable
        this->field_0x50 = &PTR_LAB_00d84fb0;   // initially set
        // Global pointer to singleton
        DAT_01130034 = this;
        // Offset +0x54: second interface vtable
        this->field_0x54 = &PTR_LAB_00d84f88;
        // Offset +0x58: third interface vtable
        this->field_0x58 = &PTR_LAB_00d84f98;
        // Zero fields
        this->field_0x5C = 0;   // offset +0x5C
        this->field_0x60 = 0;   // offset +0x60

        // Override primary vtable at offset +0x00
        this->vtable = &PTR_FUN_00d85008;  // derived class vtable
        // Override secondary vtable at offset +0x10
        this->field_0x10 = &PTR_LAB_00d84fe0;  // secondary vtable

        // Re-set some interface vtables (final overrides)
        this->field_0x50 = &PTR_LAB_00d84fdc;  // +0x50
        this->field_0x54 = &PTR_LAB_00d84fcc;  // +0x54
        this->field_0x58 = &PTR_LAB_00d84fb4;  // +0x58

        // Zero more fields
        this->field_0x64 = 0;   // +0x64
        this->field_0x68 = 0;   // +0x68
        this->field_0x6C = 0;   // +0x6C

        return;
    }
};