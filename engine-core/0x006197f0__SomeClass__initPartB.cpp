// FUNC_NAME: SomeClass::initPartB
void __thiscall SomeClass::initPartB(int this) {
    // Call base initialization or some setup function
    FUN_00612e00(); // likely base class constructor or common init

    // Zero out data at offsets 0xa4 through 0xbc (7 dwords)
    *(int *)(this + 0xa4) = 0; // +0xa4: member1 (e.g., m_pSomePtr)
    *(int *)(this + 0xa8) = 0; // +0xa8: member2
    *(int *)(this + 0xac) = 0; // +0xac: member3
    *(int *)(this + 0xb0) = 0; // +0xb0: member4
    *(int *)(this + 0xb4) = 0; // +0xb4: member5
    *(int *)(this + 0xb8) = 0; // +0xb8: member6
    *(int *)(this + 0xbc) = 0; // +0xbc: member7
}