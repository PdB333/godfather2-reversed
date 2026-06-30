// FUNC_NAME: FamilyList::initFromGlobalDefinitionList
void FamilyList::initFromGlobalDefinitionList()
{
    // Initialize dynamic array: first three ints are pointer, size, capacity
    this->data = nullptr;    // +0x00: pointer to array of ints
    this->size = 0;          // +0x04: number of elements
    this->capacity = 0;      // +0x08: allocated capacity (in elements)

    // Retrieve global definition list (function returns pointer to a struct)
    // The struct layout:
    //   +0x00: some handle or pointer (unused here except for null check)
    //   +0x04: pointer to array of 8‑byte pairs (first int = key, second = value)
    //   +0x08: count of pairs
    GlobalPairList* globalList = (GlobalPairList*)FUN_004988f0(&stackVar);
    if (globalList == nullptr)
    {
        return;
    }

    int* src = (int*)globalList->data;   // start of pairs (pointing to first int of first pair)
    int count = globalList->pairCount;   // number of pairs in source

    for (int i = 0; i < count; ++i)
    {
        // Grow capacity if needed (doubling strategy)
        if (this->size == this->capacity)
        {
            int newCapacity = (this->capacity == 0) ? 1 : (this->capacity * 2);
            FUN_00499390(newCapacity);   // reallocate/resize internal buffer (modifies this->data & this->capacity)
        }

        // Copy only the first int (key) from each source pair
        this->data[this->size] = *src;   // copy key
        this->size++;

        // Advance source pointer to next pair (skip both ints of current pair)
        src += 2;
    }
}