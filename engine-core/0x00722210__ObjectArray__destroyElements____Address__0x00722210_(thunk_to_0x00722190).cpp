// FUNC_NAME: ObjectArray::destroyElements // Address: 0x00722210 (thunk to 0x00722190)
// Role: Destructor-like function that iterates through an array of 0x24-byte objects,
//       releases non-null objects, then frees the container.

void __thiscall ObjectArray::destroyElements(void* this) {
    int* dataPtr;       // pointer to the start of the element array
    int elementCount;   // number of elements (stored at dataPtr[-4])
    int* current;       // pointer to current element (moving backward)
    int iter;           // loop counter

    dataPtr = *(int**)((char*)this + 0xC);  // +0xC: pointer to array of elements

    if (dataPtr != 0) {
        elementCount = *(int*)((char*)dataPtr - 4);  // size stored before array
        current = (int*)((char*)dataPtr + elementCount * 0x24);

        for (iter = elementCount; iter > 0; --iter) {
            current = (int*)((char*)current - 0x24);   // move to previous element
            if (*current != 0) {
                FUN_004daf90(current);  // release the object at current
            }
        }

        FUN_009c8f10((char*)dataPtr - 4);  // free the container header (size + array)
    }
}