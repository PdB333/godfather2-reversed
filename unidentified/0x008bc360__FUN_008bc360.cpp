// FUNC_NAME: UnknownClass::constructor
// Address: 0x008bc360
// Probably an EA EARS engine class constructor, possibly for a game entity or component.
// Calls a base initializer (FUN_0046c590) with the second parameter (likely an ID or parent pointer).
// Sets vtable pointer and several member pointers/constants, then zeros many fields.

class UnknownClass {
public:
    // Offsets set in constructor: (relative to this pointer)
    // +0x00: vtable pointer
    // +0x3C: PTR_LAB_00d7bc20 (pointed to by param_1[0xf])
    // +0x48: PTR_LAB_00d7bc1c (pointed to by param_1[0x12])
    // +0x50: int field (param_1[0x14])
    // +0x54: int field (param_1[0x15])
    // +0x58: short field (param_1[0x16])
    // +0x5A: short field (calculated offset)
    // +0x5C: int field (param_1[0x17])
    // +0x60: int field (param_1[0x18])
    // +0x64: int field (param_1[0x19])
    // +0x68: int field (param_1[0x1a])
    // +0x6C: int field (param_1[0x1b])
    // Object size at least 0x70 bytes.

    void* m_vtable;                     // 0x00
    // unknown padding to 0x3C
    void* m_pSomePointer1;              // 0x3C
    // more padding to 0x48
    void* m_pSomePointer2;              // 0x48
    int m_nZero1;                       // 0x50
    int m_nZero2;                       // 0x54
    short m_nShort1;                    // 0x58
    short m_nShort2;                    // 0x5A
    int m_nZero3;                       // 0x5C
    int m_nZero4;                       // 0x60
    int m_nZero5;                       // 0x64
    int m_nZero6;                       // 0x68
    int m_nZero7;                       // 0x6C
};

// Replacement for FUN_0046c590 (not provided, assume base class constructor)
void __thiscall baseConstructor(void* param_2);

UnknownClass* __thiscall FUN_008bc360(UnknownClass* this, void* param_2) {
    baseConstructor(param_2);    // likely calls a base class constructor with param_2

    this->m_nZero1 = 0;                   // param_1[0x14] = 0
    this->m_vtable = (void*)0x00d7bc30;   // set vtable (PTR_FUN_00d7bc30)
    this->m_pSomePointer1 = (void*)0x00d7bc20;  // PTR_LAB_00d7bc20
    this->m_pSomePointer2 = (void*)0x00d7bc1c;  // PTR_LAB_00d7bc1c
    this->m_nZero2 = 0;                   // param_1[0x15] = 0
    this->m_nShort1 = 0;                  // *(undefined2 *)(param_1 + 0x16) = 0
    this->m_nShort2 = 0;                  // *(undefined2 *)((int)param_1 + 0x5a) = 0
    this->m_nZero3 = 0;                   // param_1[0x17] = 0
    this->m_nZero4 = 0;                   // param_1[0x18] = 0
    this->m_nZero5 = 0;                   // param_1[0x19] = 0
    this->m_nZero6 = 0;                   // param_1[0x1a] = 0
    this->m_nZero7 = 0;                   // param_1[0x1b] = 0

    return this;
}