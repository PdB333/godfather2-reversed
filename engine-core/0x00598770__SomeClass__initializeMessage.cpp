// FUNC_NAME: SomeClass::initializeMessage
unsigned int __thiscall SomeClass::initializeMessage(int this, int param0) // param0 might be missing from decompiled
{
    int vtablePtr; // from DAT_01205590
    int stackVar1;
    int stackVar2;

    stackVar1 = 0x602; // Message type or flags
    stackVar2 = 0xc;   // Size or other constant
    uStack_10 = 2;      // Count or sub-type
    puStack_14 = &stackVar1;
    auStack_1c[0] = 0x59879b; // Possible string literal or address

    // Call vtable entry at offset 0x10 on global object (singleton)
    (*(code (**)(void))(**DAT_01205590 + 0x10))();

    auStack_1c[0] = 2;
    // Call same vtable entry with (this+2, &uStack_10)
    (*(code (**)(int, int*))(**DAT_01205590 + 0x10))(this + 2, &uStack_10);
    // Call with (this+4, &puStack_14, 4)
    (*(code (**)(int, int**, int))(**DAT_01205590 + 0x10))(this + 4, &puStack_14, 4);
    // Call with (this+8, auStack_1c, 4)
    (*(code (**)(int, int*, int))(**DAT_01205590 + 0x10))(this + 8, auStack_1c, 4);

    return 0xc; // Size of initialized block
}