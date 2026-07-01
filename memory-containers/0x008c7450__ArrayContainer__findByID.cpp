// FUNC_NAME: ArrayContainer::findByID
uint __thiscall ArrayContainer::findByID(int id)
{
    uint index = 0;
    // this+0x28: number of elements
    uint count = *(uint *)(this + 0x28);
    if (count != 0) {
        // this+0x24: pointer to array of pointers to elements
        int **items = *(int ***)(this + 0x24);
        do {
            // each element has an ID at offset 0x54
            if (*(int *)(*items + 0x54) == id) {
                // Found: return packed index (high 24 bits) with low byte = 1
                return (index << 8) | 1;
            }
            index++;
            items++;
        } while (index < count);
    }
    // Not found: return count << 8 (high 24 bits) with low byte = 0
    return (index << 8);
}