// FUNC_NAME: UnknownClass::updateBehaviorState
// Address: 0x00778e70
// Role: Updates behavior state based on some internal data, possibly animation or AI decision.
void __thiscall UnknownClass::updateBehaviorState() {
    // Offset: +0x5C (some state object pointer)
    int someStatePtr = *(int*)((char*)this + 0x5C);
    int outputData = 0;
    int outputData2 = 0;

    int* internalObj = nullptr;
    // Offset: +0x88 (pointer to internal object)
    if (*(int*)((char*)this + 0x88) != 0) {
        internalObj = (int*)(*(int*)((char*)this + 0x88) - 0x48);
    }
    // Virtual call on internalObj at vtable offset 0x1F8 (index 126)
    // Signature: void getBehaviorData(int someStatePtr, int* outData)
    (*(void(__thiscall**)(int, int*))(*(int*)internalObj + 0x1F8))(someStatePtr, &outputData);

    char flag1 = sub_008754b0(&outputData);
    int result;
    if (flag1 == 0) {
        flag1 = sub_008754e0(&outputData);
        result = (-((uint)(flag1 != 0)) & 0x5A8F2B0E) + 0xA1C0912A;
    } else {
        flag1 = sub_008754e0(&outputData);
        result = (-((uint)(flag1 != 0)) & 0x9F9137E6) + 0x6E26083E;
    }

    if (*(int*)((char*)this + 0x88) != 0 && *(int*)((char*)this + 0x88) != 0x48) {
        result = sub_00875AF0(someStatePtr, result);
    }

    char flag2 = sub_0045F1B0(result);
    if (flag2 != 0) {
        // Virtual call on this at vtable offset 0x2C (index 11)
        // Signature: void applyResult(int result, int a, int b, int c, float d, float e)
        (*(void(__thiscall**)(int, int, int, int, float, float))(*(int*)this + 0x2C))(result, 1, 1, 0, 1.0f, 1.0f);
    }
}