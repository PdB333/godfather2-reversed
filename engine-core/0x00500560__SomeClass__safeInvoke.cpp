// FUNC_NAME: SomeClass::safeInvoke
// Address: 0x00500560
// Conditional wrapper: if the condition is non-zero, delegates to FUN_00500120 with this pointer; otherwise returns 0.
int SomeClass::safeInvoke(int condition) {
    if (condition != 0) {
        // Calls the primary handler (likely a getter or action method)
        return FUN_00500120(this); // +0x00
    }
    return 0;
}