// FUNC_NAME: Entity::constructor
void __thiscall Entity::constructor(void* this, uint param1, uint param2) {
    void* defaultThis;
    void* local_24[1]; // +0x00: placeholder
    uint local_20;      // +0x04: stores param2
    uint local_1c;      // +0x08: zeroed
    uint local_18;      // +0x0C: zeroed
    void* vtablePtr;    // +0x10: vtable pointer
    void* local_10;     // +0x14: pointer to local_24
    void* local_c;      // +0x18: pointer to this or default

    local_10 = (void*)local_24;
    local_20 = param2;
    if (this == (void*)0x0) {
        defaultThis = &DAT_00e41518; // default static instance
    } else {
        defaultThis = this;
    }
    vtablePtr = &LAB_00629260; // vtable at 0x00629260
    local_1c = 0;
    local_18 = 0;
    local_c = defaultThis;
    FUN_00638520(); // base class initialization (e.g., zero fields)
    FUN_006366f0(param1); // specific initialization with param1
    return;
}