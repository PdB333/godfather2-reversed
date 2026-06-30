// FUNC_NAME: SomeClass::setInitialState

// Sets initial state fields: state (0x10=9), subState (0x14=2), and a parameter (0x18=param2)
void __thiscall SomeClass::setInitialState(int this, int param2) {
    *(int*)(this + 0x18) = param2;   // +0x18: probably a user-defined value
    *(char*)(this + 0x14) = 2;      // +0x14: byte field, possibly enum value
    *(int*)(this + 0x10) = 9;       // +0x10: int field, likely main state ID
}