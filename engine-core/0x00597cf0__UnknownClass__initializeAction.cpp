// FUNC_NAME: UnknownClass::initializeAction
unsigned int __thiscall UnknownClass::initializeAction(void) {
    // Function at 0x00597cf0
    // Assumed __thiscall: this pointer in ECX (Ghidra shows in_EAX)
    int thisPtr = /* ECX */;
    int stackVar1; // local_8, holds 0x207
    int* stackPtr2; // puStack_14, pointer to stackVar1
    int stackVar3; // uStack_10, holds 2
    int stackArr[2]; // auStack_1c, initially 0x597d1b then set to 2

    stackVar3 = 2;
    stackPtr2 = &stackVar1;
    stackVar1 = 0x207;
    stackArr[0] = 0x597d1b; // Possibly a vtable or debug address

    // First virtual call: likely constructor or init on the object itself
    (*(code**)(*(int*)g_globalVTable + 0x10))();

    stackArr[0] = 2;

    // Copy 4 bytes from &stackVar3 to offset +2
    (*(code**)(*(int*)g_globalVTable + 0x10))(thisPtr + 2, &stackVar3, 4);
    // Copy 4 bytes from stackVar1 (0x207) to offset +4 via pointer indirection
    (*(code**)(*(int*)g_globalVTable + 0x10))(thisPtr + 4, &stackPtr2, 4);
    // Copy 4 bytes from stackArr[0] (2) to offset +8
    (*(code**)(*(int*)g_globalVTable + 0x10))(thisPtr + 8, stackArr, 4);

    return 0xC; // Size of object? (12 bytes)
}