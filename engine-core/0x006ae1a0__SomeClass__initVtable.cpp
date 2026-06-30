// FUNC_NAME: SomeClass::initVtable
char __thiscall SomeClass::initVtable(int this, uint param2, uint param3) {
    uint *vtablePtr; // local_10: from this+0x180
    uint globalData = DAT_0112a5d8; // local_20, global constant
    uint vtableLabel = *PTR_LAB_00d5dbb4; // local_14, dereferenced label
    uint *ppVtable = &vtableLabel; // local_1c
    uint arg2 = param2; // local_c
    uint arg3 = param3; // local_8
    char result = 0; // local_4
    char pad = 0; // local_18

    vtablePtr = *(uint **)(this + 0x180); // store pointer from offset 0x180
    // Setup data for base initialization
    FUN_00408a00(&globalData, 0); // call base class constructor or init routine
    return result; // always 0
}