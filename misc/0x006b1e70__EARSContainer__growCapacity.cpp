// FUNC_NAME: EARSContainer::growCapacity
void __thiscall EARSContainer::growCapacity(int* container, uint newCapacity)
{
    int* oldData;
    int* newData;
    uint i;
    int* newElem;
    int* oldElem;
    int* objPtr;
    int* nextPtr;

    if ((uint)container[2] < newCapacity) {
        newData = (int*)FUN_009c8e80(newCapacity * 8); // allocate new array of 8-byte elements
        if (*container != 0) {
            i = 0;
            newElem = newData;
            if (container[1] != 0) {
                do {
                    oldElem = (int*)(*container + i * 8);
                    if (newElem != (int*)0x0) {
                        objPtr = (int*)*oldElem;
                        *newElem = (int)objPtr;
                        newElem[1] = 0;
                        if (objPtr != (int*)0x0) {
                            newElem[1] = *(int*)(objPtr + 1); // copy next pointer from object
                            *(int**)(objPtr + 1) = newElem; // update object's back-pointer to new node
                        }
                    }
                    if (*oldElem != 0) {
                        FUN_004daf90(oldElem); // detach old node from object
                    }
                    i++;
                    newElem += 2; // advance to next 8-byte slot
                } while (i < (uint)container[1]);
            }
            FUN_009c8f10(*container); // free old array
        }
        *container = (int)newData;
        container[2] = newCapacity;
    }
    return;
}