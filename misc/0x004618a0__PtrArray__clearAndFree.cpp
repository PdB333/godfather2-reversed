// FUNC_NAME: PtrArray::clearAndFree
void __thiscall PtrArray::clearAndFree(PtrArray* this)
{
    int index;            // iVar1
    int arrayPtr;         // iVar2
    int elementPtr;       // iVar3

    index = this->mCount;
    while (index = index - 1, index >= 0) {
        arrayPtr = this->mArray;
        elementPtr = *(int*)(arrayPtr + index * 4);
        if (elementPtr != 0) {
            *(int*)(elementPtr + 8) = 0;        // +0x08: clear back pointer or ref count
            *(int*)(arrayPtr + index * 4) = 0;  // remove pointer from array
        }
    }
    this->mCount = 0;
    deallocate(this->mArray);   // free the dynamic array
    this->mArray = 0;
    this->mExtra = 0;           // +0x08: clear auxiliary field
}