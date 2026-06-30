// FUNC_NAME: GameManager::constructor
class GameManager : public BaseClass1, public BaseClass2 {
public:
    GameManager() {
        // +0x00: vtable for first base class
        *(void**)this = &PTR_FUN_00e30eac;
        // +0x04: temporary vtable for second base class, then overwritten below
        *(void**)((char*)this + 4) = &PTR_LAB_00e30ebc;
        // Global pointer assignment (DAT_012233f0)
        g_gameManager = this;

        // Reassert first vtable (likely inlined base constructor)
        *(void**)this = &PTR_FUN_00e30eac;
        // +0x04: final vtable for second base class
        *(void**)((char*)this + 4) = &PTR_LAB_00e30eb8;
        // +0x08: int field initialized to 0
        this->field_08 = 0;
        // +0x0C: byte field initialized to 0
        *(char*)((char*)this + 0x0C) = 0;
        // +0x4C: int field initialized to 0
        this->field_4C = 0;
        // +0x50: byte field initialized to 0
        *(char*)((char*)this + 0x50) = 0;

        // Initialize sub-system with code 6
        FUN_00439b20(6);
        // Call additional initialization on this object
        FUN_0043e2e0(this);
    }

private:
    void* vtable1;          // +0x00
    void* vtable2;          // +0x04
    int field_08;           // +0x08
    char byte_0C;           // +0x0C
    // ... other fields ...
    int field_4C;           // +0x4C
    char byte_50;           // +0x50
};

// External global pointer, set during construction
extern GameManager* g_gameManager; // originally DAT_012233f0