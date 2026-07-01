// FUNC_NAME: UIButton::setActive
void __thiscall UIButton::setActive(int thisPtr, int active) {
    int behaviorPtr;
    int* vtable;
    int value1, value2;
    short value3;

    if (active != 0) {
        *(int*)(thisPtr + 0x78) = *(int*)(thisPtr + 0x78) + 1; // +0x78: activationCount
        FUN_0097b630(0, 1); // some initialization
    }
    *(int*)(thisPtr + 0x6c) = active; // +0x6c: currentState

    behaviorPtr = *(int*)(thisPtr + 0x54 + active * 4); // +0x54: behaviorArray[2]
    if (*(char*)(thisPtr + 0x50) == '\0') { // +0x50: isActive flag
        FUN_00957e10(); // handle inactive state
    }

    vtable = *(int**)behaviorPtr;
    (*(code**)(vtable[0x6c / 4]))(); // vtable+0x6c: onActivate?
    value1 = (*(code**)(vtable[0x74 / 4]))(); // vtable+0x74: getSomeValue1
    *(int*)(thisPtr + 0x74) = value1; // +0x74: storedValue1
    value2 = (*(code**)(vtable[0x70 / 4]))(); // vtable+0x70: getSomeValue2
    *(int*)(thisPtr + 0x70) = value2; // +0x70: storedValue2
    (*(code**)(vtable[0x8c / 4]))(DAT_01130030); // vtable+0x8c: doSomethingWithGlobal
    value1 = (*(code**)(vtable[0x98 / 4]))(); // vtable+0x98: getSomeValue3
    FUN_0097de80(value1);
    value1 = (*(code**)(vtable[0x84 / 4]))(); // vtable+0x84: getSomeValue4
    FUN_00976370(value1);
    value3 = (*(code**)(vtable[0x94 / 4]))(); // vtable+0x94: getSomeValue5
    FUN_00979b10(value3);
    FUN_00956930(active);
    FUN_00954870();

    // Add callbacks to a list at +0x14
    int listHead = thisPtr + 0x14; // +0x14: callbackList
    FUN_005c0d50(listHead, &LAB_005bfc10, 0);
    FUN_005c0d50(listHead, &LAB_009573e0, 0);
    FUN_005c0d50(listHead, &LAB_005bfbe0, 0);
    FUN_0094b250();

    if (active != 0) {
        FUN_005a04a0("ActivateButton", 0, &DAT_00d8c174, 1, PTR_DAT_00e57434);
        return;
    }
    FUN_005a04a0("DeactivateButton", 0, &DAT_00d8c174, 1, PTR_DAT_00e57434);
    if (*(char*)(thisPtr + 0x50) == '\0') {
        FUN_005a04a0("ActivateButton", 0, &DAT_00d8c174, 1, PTR_DAT_00e5743c);
        return;
    }
    FUN_005a04a0("DeactivateButton", 0, &DAT_00d8c174, 1, PTR_DAT_00e5743c);
}