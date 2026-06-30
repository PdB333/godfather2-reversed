// FUNC_NAME: ScriptIterator::advanceAndGetValue

int __thiscall ScriptIterator::advanceAndGetValue(ScriptIterator* this) {
    int** pCurrent = *(int***)(this + 0xC); // +0xC: pointer to current iterator position
    int* pEnd = *(int**)(this + 0x8);       // +0x8: pointer to end of iteration range
    
    // CONCAT44 combines pEnd (high) and pCurrent (low) into a 64-bit value for bounds checking
    __int64 combined = (__int64)pEnd << 32 | (unsigned int)pCurrent;
    
    // Check if iterators are valid and we haven't reached the end
    if ((pEnd <= pCurrent) || (pCurrent == nullptr) || (*pCurrent == -1)) {
        // Error: expected value but iterator is invalid
        FUN_00627a20(this, 1, "value expected");
        // extraout_ECX is used but not stored? Possibly a side effect.
        // Actually the decompiler shows iVar2 = extraout_ECX, but it's unused in the error path.
        // We'll ignore the extraout_ECX assignment.
    }
    
    // Re-evaluate bounds using the 64-bit comparison: lower 32 bits (pCurrent) < upper 32 bits (pEnd)
    // and pCurrent != 0, and the current element is not the sentinel -1
    if ((((unsigned int)combined < (unsigned int)(combined >> 32)) && ((unsigned int)combined != 0)) && (*pCurrent != -1)) {
        int index = *pCurrent; // Dereference current pointer to get an index into a string table
        // Retrieve string from global table at PTR_DAT_00e2a89c using the index
        const char* value = (&PTR_DAT_00e2a89c)[index]; // +0x? table of string pointers
        // Push/return the value (likely into a Lua stack)
        FUN_00625ca0(this, value);
        return 1; // Indicate success, one value returned
    }
    
    // No value available at current iterator position
    FUN_00625ca0(this, "no value");
    return 1; // Still returns 1 (likely Lua convention: always returns a value)
}