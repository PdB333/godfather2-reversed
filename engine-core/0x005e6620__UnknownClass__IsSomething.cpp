// FUNC_NAME: UnknownClass::IsSomething
// Function address: 0x005e6620
// Role: Calls a virtual function at vtable offset 0x34 on a global object (DAT_01223510), passing a parameter, returns bool.
// The global DAT_01223510 likely points to a class instance with a vtable, possibly a manager or singleton.

extern int* DAT_01223510; // Points to a vtable pointer (base of class instance?)

bool UnknownClass::IsSomething(void* param) {
    // Call virtual function at vtable offset 0x34 (index 13, assuming 4-byte function pointers)
    // The function signature is bool (*)(void*) based on usage.
    char result;
    result = ((char (*)(void*))(*(int**)*DAT_01223510)[0x34 / 4])(param);
    return result != '\0';
}