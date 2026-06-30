// FUNC_NAME: ArrayContainer::removeAt
void __thiscall ArrayContainer::removeAt(int* this, int index)
{
    // this[0] = pointer to array of 12-byte elements
    // this[1] = number of elements (size)
    char* pBase = (char*)this[0];
    int count = this[1];

    // If index is not the last element, destroy the last element before
    // the logical removal (the last element will be overwritten if moved,
    // but here only the last element is destroyed and count decremented).
    if (index != count - 1) {
        char* lastElement = pBase + (count - 1) * 12; // base + (size-1)*12
        destroyElement(lastElement); // FUN_007294d0 – likely destructor/cleanup
    }

    // Reduce element count
    this[1] = count - 1;

    // After shrinking, check if the new last element has a non-zero field
    // at offset +4 (e.g., a pointer or reference count).
    int* field4 = (int*)(pBase + 4 + this[1] * 12); // offset 4 of element[newCount]
    if (*field4 != 0) {
        doGlobalCleanup(); // FUN_004daf90 – conditionally called handler
    }
}