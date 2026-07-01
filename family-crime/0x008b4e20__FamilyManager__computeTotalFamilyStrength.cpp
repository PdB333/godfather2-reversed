// FUNC_NAME: FamilyManager::computeTotalFamilyStrength
// Address: 0x008b4e20
// This function iterates over a list of family-related objects (businesses, properties, etc.)
// and sums a value retrieved from a lookup table using each object's field at offset +8.
// The iteration is initialized by calling startIteration on a list stored at +0x60 and
// using contextId (param_2) and flag 0. The lookup table is stored at +0x108.
// Returns the total as an int (converted from short sum).

__thiscall int FamilyManager::computeTotalFamilyStrength(int contextId)
{
    // +0x60: pointer to a list/container of family objects (e.g., list of BusinessNode)
    // +0x108: pointer to a value table (e.g., base income or influence values)
    void* list = *(void**)(this + 0x60);
    void* table = *(void**)(this + 0x108);

    // Initialize the iterator over the list (possible begins a traversal)
    // FUN_008b3fb0 takes (list, contextId, flag=0) and likely returns/exposes an iterator
    startIteration(list, contextId, 0);

    short total = 0;

    // Iterator internal state (decompiler simplification; actually managed by iterator object)
    int iteratorState1;
    int iteratorState2;
    IteratorFuncs* iterator; // pointer to struct with two function pointers

    // While loop checks if iterator is still valid (states non-zero)
    while (iteratorState1 != 0 || iteratorState2 != 0)
    {
        // Call first function pointer to get current item (returns pointer to object)
        // The vtable/function pointer is at iterator[0]
        int* currentItem = (int*)(*(int (**)(void))(*iterator))();

        // Retrieve short from lookup table using the item's field at offset +8
        // FUN_004bb3b0 takes (table, fieldValue) and returns a short value
        short value = getValueFromTable(table, *(int*)(currentItem + 8));
        total += value;

        // Call second function pointer to advance iterator (iterator[1])
        (*(void (**)(void))(iterator[1]))();
    }

    return (int)total;
}

// External helper functions (declared elsewhere)
void startIteration(void* list, int contextId, int flag);
short getValueFromTable(void* table, int index);