// FUNC_NAME: ObjectArray::destroy
void __thiscall ObjectArray::destroy() {
    // param_1 is this: struct { int* mArray; int mCount; } at +0x00 and +0x04
    int countMinusOne = this->mCount - 1;
    if (countMinusOne >= 0) {
        int elementOffset = countMinusOne * 12; // each element is 12 bytes
        do {
            // Check if the first field of the element (likely a pointer/handle) is non-zero
            if (*(int*)((char*)this->mArray + elementOffset) != 0) {
                // Call element destructor (FUN_004daf90) with pointer to the element
                elementDestructor((void*)((char*)this->mArray + elementOffset));
            }
            countMinusOne--;
            elementOffset -= 12;
        } while (countMinusOne >= 0);
    }
    if (this->mArray != 0) {
        // Free the array memory (FUN_009c8f10 is likely operator delete)
        operatorDelete(this->mArray);
    }
}

// External functions referenced:
// void __cdecl elementDestructor(void* element);  // 0x004daf90
// void __cdecl operatorDelete(void* ptr);         // 0x009c8f10