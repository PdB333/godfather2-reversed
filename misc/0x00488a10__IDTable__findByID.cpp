// FUNC_NAME: IDTable::findByID
uint __thiscall IDTable::findByID(int param_2)
{
    // +0x00: vtable? (not used)
    // +0x08: m_pArray – pointer to array of pointers to IDObject (each object's first member is int ID)
    // +0x0c: m_count – number of elements in the array
    // +0x1c: m_pFound – pointer to last found IDObject

    int searchKey;
    int* pCurrent;
    int** ppEntry;
    int** ppEnd;

    // Use global static as search key if non-zero; otherwise use the parameter
    searchKey = DAT_01163d90;   // Global static – set externally before calling this method
    if (DAT_01163d90 == 0) {
        searchKey = param_2;
    }

    ppEntry = *(int***)(this + 8);   // m_pArray
    ppEnd = ppEntry + *(int*)(this + 0xc); // m_count

    if (ppEntry != ppEnd) {
        do {
            pCurrent = *ppEntry;   // dereference pointer to IDObject (first field is ID)
            if (*pCurrent == searchKey) {
                *(int**)(this + 0x1c) = pCurrent; // store found object pointer in m_pFound
                // Return pointer with low byte set to 1 to indicate success
                return (reinterpret_cast<uint>(pCurrent) & 0xFFFFFF00) | 1;
            }
            ppEntry++;
        } while (ppEntry != ppEnd);
    }

    // Not found: return pointer value of end iterator with low byte cleared
    return reinterpret_cast<uint>(ppEntry) & 0xFFFFFF00;
}