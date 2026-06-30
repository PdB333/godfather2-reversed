// FUNC_NAME: genericConstructor
// Function at 0x004f3dc0 – Constructs an object with a vtable and optional additional init based on a parent flag.
// param_1: pointer to a parent object (byte at offset +0xD is a flag)
// param_2: pointer to uninitialized object memory (can be null)
// Returns param_2 on success, or null if param_2 was null.

void* genericConstructor(void* param_1, void* param_2) {
    if (param_2 != nullptr) {
        baseInit();                                           // FUN_00533cc0 – likely a base class or global init
        *(void**)param_2 = (void*)0x00e37710;                 // set vtable pointer (+0x0)
        if (*(char*)((uint8_t*)param_1 + 0xD) == '\0') {     // check flag at parent +0xD
            additionalInit();                                 // FUN_004f42f0 – fills additional members
        }
        return param_2;
    }
    return nullptr;
}