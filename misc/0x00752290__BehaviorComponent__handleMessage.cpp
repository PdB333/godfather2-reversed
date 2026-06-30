// FUNC_NAME: BehaviorComponent::handleMessage
int __thiscall BehaviorComponent::handleMessage(int *this, int a2, int a3, int a4, int messageId, int a6) {
    int result;
    switch (messageId - 0x12) {
    case 0:
        // +0xC8 (index 50): set timer/state to a global
        this[50] = DAT_01205228;
        return 1;
    case 1:
        sub_751e70();
        return 1;
    case 2:
        sub_751ec0();
        return 1;
    case 3:
        break; // fall through to special handling
    case 4:
        sub_7f9340(1, 0);
        // +0xCC (index 51): set bit 5 (0x20)
        this[51] |= 0x20;
        return 1;
    case 5:
        // +0xCC (index 51): clear bit 4 (0x10)
        this[51] &= 0xFFFFFFEF;
        return 1;
    case 6:
        sub_752000();
        return 1;
    default:
        return sub_80e8e0(a2, a3, a4, messageId, a6);
    }

    // case 3: call a function pointer and then a vtable method
    if (this[57] == 0) { // +0xE4 (index 57): alternate callback
        result = ((int (*)())this[52])(); // +0xD0 (index 52): primary callback
    } else {
        result = ((int (*)(int *))this[57])(&this[52]);
    }
    // vtable offset 0x2c: function taking (int, int, int, int, float, float)
    (*(void (**)(int, int, int, int, float, float))(*(int *)this + 0x2c))(result, 1, 0, 0, 1065353216, 1065353216);
    return 1;
}