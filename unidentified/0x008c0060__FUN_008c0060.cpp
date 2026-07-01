// FUNC_NAME: unknown::countValidItems
// Address: 0x008c0060
// Role: Counts the number of items (possibly active entities or controllers) by looping over a count field at offset 0x1a8
//        and checking each via the callee `isItemActive()` (FUN_008c8110). The callee appears to take no arguments,
//        suggesting it queries a global or object-specific state not captured in the decompiler's signature.

int __fastcall countValidItems(int this) {
    int validCount = 0;
    unsigned int i = 0;

    // +0x1a8: number of items to iterate over (e.g., array length, active slot count)
    if (*(int *)(this + 0x1a8) != 0) {
        do {
            // Call to FUN_008c8110; returns non-zero if item is considered valid/active
            if (FUN_008c8110() != 0) {
                validCount = validCount + 1;
            }
            i = i + 1;
        } while (i < *(uint *)(this + 0x1a8));
    }
    return validCount;
}