// FUNC_NAME: conditionalCallWithGuard
// Function at 0x0049ead0: Calls a second function from a callback table only if the first callback returns non-zero OR a specific flag (bit 0 of offset 0xB2) is set.
typedef char (__cdecl *PredicateFunc)();                           // returns 0 for "block", non-zero for "allow"
typedef void (__cdecl *ActionFunc)(void* obj);                     // performs the guarded action

void conditionalCallWithGuard(void* obj, void** callbackTable)
{
    // dereference callbackTable[0] to get predicate function pointer
    PredicateFunc predicate = (PredicateFunc)callbackTable[0];
    char shouldAllow = predicate();
    
    // check if predicate returned false OR the object's flag at +0xB2 (bit 0) is set
    if (shouldAllow == 0 || (*(uint8_t*)((uintptr_t)obj + 0xB2) & 1) != 0) {
        // call the action function with the object as argument
        ActionFunc action = (ActionFunc)callbackTable[1];
        action(obj);
    }
}