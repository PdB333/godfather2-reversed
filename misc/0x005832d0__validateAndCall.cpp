// FUNC_NAME: validateAndCall
// Function at 0x005832d0: checks two non-null pointers (likely this and some argument) then calls a helper function.
// Possibly used to safely invoke a getter or operation only when both objects are valid.
int __fastcall validateAndCall(void* object, int secondaryParam) {
    // object passed in EAX (unusually), secondaryParam in param_1 (likely ECX or EDX)
    if (object != 0 && secondaryParam != 0) {
        return FUN_005848f0(); // returns an int; exact purpose unknown
    }
    return 0;
}