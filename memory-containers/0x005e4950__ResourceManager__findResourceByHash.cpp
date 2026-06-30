// FUNC_NAME: ResourceManager::findResourceByHash
// Address: 0x005e4950
// Role: Lookup and return a resource by a global hash key (DAT_01223514). 
// Possibly used to retrieve a data object from a manager. The local variable `bFlag` is initialized to 0 and never modified, so the condition always fails, making this function always return 0. This may be a debug stub or the decompilation missed an assignment.

int __thiscall ResourceManager::findResourceByHash(int this) {
    int hashResult;             // iVar1
    char outBuffer;             // local_5 - buffer for lookup result
    int bFlag = 0;              // local_4 - flag (always 0 in this version)

    // Lookup using the global hash/string key DAT_01223514
    hashResult = FUN_005f0600(DAT_01223514, &outBuffer);
    if (hashResult != 0 && bFlag != 0) {
        // If lookup succeeded and flag is set (never), convert/retrieve the result
        return FUN_005e4a20(this, hashResult);
    }
    return 0; // Always returns 0 due to bFlag being 0
}