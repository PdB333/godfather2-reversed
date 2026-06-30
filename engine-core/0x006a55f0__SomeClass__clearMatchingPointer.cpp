// FUNC_NAME: SomeClass::clearMatchingPointer
void __thiscall SomeClass::clearMatchingPointer(int *pGivenPointer) // param_2: pointer to an int that holds the address to compare
{
    // Stored pointer at offset 0x694 (likely a component or resource pointer)
    int *pStored = (int *)(this + 0x694);
    if (*pGivenPointer == *pStored && *pStored != 0) {
        FUN_004daf90(pStored); // Likely releases the resource (e.g., delete, free, or dec refcount)
        *pStored = 0;
    }
}