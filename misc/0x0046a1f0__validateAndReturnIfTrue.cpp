// FUNC_NAME: validateAndReturnIfTrue
uint __thiscall validateAndReturnIfTrue(void* thisPtr, uint handle) {
    int unusedOutput = 0;
    // vtable offset 0x10: virtual function that checks validity and returns a char
    char isValid = (**(char (__thiscall**)(uint, int*))((int*)thisPtr + 0x10))(handle, &unusedOutput);
    return (isValid != 0) ? handle : 0;
}