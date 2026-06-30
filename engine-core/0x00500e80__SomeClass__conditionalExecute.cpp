// FUNC_NAME: SomeClass::conditionalExecute
//--------------------------------------------------------------------------------
// Function: 0x00500e80
// Role: Wrapper that conditionally calls FUN_00500b50 based on a boolean flag.
//       Returns 0 if flag is false, otherwise returns result of the delegate function.
//--------------------------------------------------------------------------------

int __thiscall SomeClass::conditionalExecute(void* thisPtr, int enabled) {
    if (enabled != 0) {
        // Call the actual implementation (FUN_00500b50)
        return FUN_00500b50(thisPtr);
    }
    return 0;
}