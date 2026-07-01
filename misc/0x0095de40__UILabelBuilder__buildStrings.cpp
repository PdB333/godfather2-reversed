// FUNC_NAME: UILabelBuilder::buildStrings
void __thiscall UILabelBuilder::buildStrings(void* this, undefined4 param2, undefined4 param3, undefined4 param4, undefined4 param5)
{
    char* pString;
    char* local_10;
    int local_c; // Could be a size parameter, initialized to 0 in Ghidra output but likely set by getString
    void (*cleanupFunc)(char*);
    
    local_10 = 0;
    local_c = 0; // Might be an out parameter or unused
    cleanupFunc = 0;
    
    // Get first string from resource manager using ID at +0x14
    // FUN_00604000 is likely a resource string getter (e.g., "getStringFromResource")
    pString = getStringFromResource(*(unsigned int*)((char*)this + 0x14), &local_10, 1);
    if (local_10 == 0) {
        // Default empty string
        pString = &DAT_0120546e; // likely an empty string constant
    }
    // Format first output buffer using the retrieved string
    formatStringToBuffer(param2, pString, param5, local_c);
    
    // Get second string from ID at +0x4c
    // FUN_00603d30 is another string getter (maybe description)
    pString = getStringFromResource2(*(unsigned int*)((char*)this + 0x4c), &local_10, 1);
    if (local_10 == 0) {
        pString = &DAT_0120546e;
    }
    formatStringToBuffer(param3, pString, param5, local_c);
    
    // Get third string from ID at +0x50
    pString = getStringFromResource2(*(unsigned int*)((char*)this + 0x50), &local_10, 1);
    if (local_10 == 0) {
        pString = &DAT_0120546e;
    }
    formatStringToBuffer(param4, pString, param5, local_c);
    
    // Clean up: if the last retrieved non-default string is not null, call its cleanup function
    // NOTE: The decompiler shows a function pointer call (*cleanupFunc)(local_10) but cleanupFunc is never set.
    // This likely corresponds to a resource release function that was not correctly resolved.
    // Possibly it was meant to be "delete[] local_10" or a specific deallocator.
    if (local_10 != 0) {
        // (*cleanupFunc)(local_10); // Unknown cleanup; omitted due to missing target
        // In original code, might be: releaseString(local_10);
    }
}