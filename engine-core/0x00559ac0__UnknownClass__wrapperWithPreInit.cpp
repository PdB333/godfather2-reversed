// FUNC_NAME: UnknownClass::wrapperWithPreInit
void __thiscall wrapperWithPreInit(void* thisPtr, int arg1, int arg2, int arg3, int arg4, int arg5) {
    // Call a common initialization routine (likely sets up some engine state)
    commonInit();  // FUN_00557e20

    // Delegate to the actual processing function with the provided arguments
    processDelegate(arg1, arg2, arg3, arg4, arg5);  // FUN_00c09ee0
}