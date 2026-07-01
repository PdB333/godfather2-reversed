// FUNC_NAME: SimManager::constructor
// Address: 0x008cb910
// Role: Initializes the SimManager object, setting up vtable, counters, and zeroing two large arrays of 500 pairs each.

class SimManager {
public:
    // Vtable pointer at +0x00
    void* vtable;
    // +0x04: Some counter or flag, initialized to 1
    int field_4;
    // +0x08: Another counter or flag, initialized to 0
    int field_8;
    // +0x0C: First array of 500 pairs (each pair is two ints)
    struct Pair { int a; int b; } pairs1[500];
    // +0x0C + 500*8 = +0xFAC: Extra int after first array
    int extra1;
    // +0xFB0: Second array of 500 pairs
    Pair pairs2[500];
    // +0xFB0 + 500*8 = +0x1F40: Extra int after second array
    int extra2;

    // Constructor-like initialization
    __thiscall SimManager* constructor();
};

__thiscall SimManager* SimManager::constructor() {
    // Set vtable pointer (from global)
    this->vtable = &PTR_FUN_00d7c2d8; // vtable for SimManager
    this->field_4 = 1;
    this->field_8 = 0;

    // Zero first array of 500 pairs (indices 3 to 1002 in param_1 terms)
    Pair* p = this->pairs1;
    for (int i = 0; i < 500; i++) {
        p->a = 0;
        p->b = 0;
        p++;
    }
    // Set extra int after first array
    this->extra1 = 0;

    // Zero second array of 500 pairs (indices 1004 to 2003)
    p = this->pairs2;
    for (int i = 0; i < 500; i++) {
        p->a = 0;
        p->b = 0;
        p++;
    }
    // Set extra int after second array
    this->extra2 = 0;

    // Call some static initialization (likely global singleton setup)
    FUN_004086b0(&DAT_012069d4, 0);

    return this;
}