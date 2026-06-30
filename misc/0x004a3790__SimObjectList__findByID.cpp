// FUNC_NAME: SimObjectList::findByID

int __thiscall SimObjectList::findByID(int this, int id)
{
    uint i;
    int objPtr;

    i = 0;
    objPtr = 0;
    if (*(ushort *)(this + 0x20) != 0) {          // +0x20: count of elements
        int **ptrArray = *(int ***)(this + 0x1c); // +0x1c: array of pointers to objects
        while (true) {
            objPtr = *ptrArray;                   // current object pointer
            if (id == *(int *)(objPtr + 0x10)) {  // +0x10: object ID field
                break;
            }
            i++;
            ptrArray++;
            if (*(ushort *)(this + 0x20) <= i) {
                return 0;                         // not found
            }
        }
    }
    return objPtr;                                // return found object pointer, or 0 if not found
}