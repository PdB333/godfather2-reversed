// FUNC_NAME: SomeClass::testAndReturnMask
uint SomeClass::testAndReturnMask(int *thisPtr, uint param_2) {
    // +0x10 virtual method: likely checks a condition based on param_2, returns bool
    char result;
    int output; // not used after call
    output = 0;
    result = (**(code (__thiscall** )(int, int*))(*thisPtr + 0x10))(param_2, &output);
    // Return param_2 if condition true, else 0
    return -(uint)(result != 0) & param_2;
}