// FUNC_NAME: SomeGameObject::initializeState (address 0x005f01f0)
// Role: Initializes internal state, including sub-object at offset +8, based on a byte parameter.
// Offsets:
//   +600: byte flag/identifier
//   +4: int field (reset to 0)
//   +8: pointer to a sub-structure (initialized via FUN_005dbc10)
//   +0xc: int field (reset to 0)
//   +0x10: short field (reset to 0)
//   +0x12: short field (reset to 0)
// Calls:
//   FUN_005f0840: condition check (returns bool)
//   FUN_005dbc10: sub-object initializer (takes pointer and int 0)
//   FUN_005f1350: final setup (returns bool)

int __thiscall SomeGameObject::initializeState(int this, char value) {
    char* pByteField = (char*)(this + 600);
    *pByteField = value;

    if (FUN_005f0840() != 0) {
        int* pField4 = (int*)(this + 4);
        *pField4 = 0;
        if ((void*)(this + 8) != (void*)0) {
            *(int*)(this + 8) = 0;
            *(int*)(this + 0xC) = 0;
            *(short*)(this + 0x10) = 0;
            *(short*)(this + 0x12) = 0;
            FUN_005dbc10(this + 8, 0);
            if (FUN_005f1350() != 0) {
                return 1;
            }
        }
    }
    return 0;
}