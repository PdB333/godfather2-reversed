// FUNC_NAME: GameEntityCollection::iterateAndCheckId
// Address: 0x0068e8f0
// Role: Iterates over a collection of game entities using a static table iterator,
//        calls a virtual method on each entity (via vtable+0x14) and returns whether
//        the passed ID matches a hardcoded zero (likely a placeholder or debugging code).
//        The loop seems to call a check function per entity but the result is not captured,
//        making the function always return (param_1 == 0).

bool GameEntityCollection::iterateAndCheckId(int param_1)
{
    // Iterator structure (static pointer table from read-only data)
    char** iterator = &PTR_LAB_00d5c86c;   // +0x00: pointer to function table for iterator
    
    int found = 0;                          // local_10: flag, never modified in this loop
    int unused = 7;                         // local_c: appears to be unused (perhaps stack padding)

    FUN_00495960();                          // iteratorInit(iterator) - initialize iteration
    char hasMore = FUN_00495980();           // iteratorHasMore(iterator)
    while (hasMore != '\0') {
        int* entityPtr = (int*)FUN_004959c0(); // iteratorGetNext(iterator) -> entity pointer
        // Call virtual method at offset 0x14 (e.g., checkCondition) with iterator address
        (**(code**)(*entityPtr + 0x14))(&iterator);
        hasMore = FUN_00495980();            // check if more elements
    }
    return found == param_1;                 // always true only if param_1 == 0
}