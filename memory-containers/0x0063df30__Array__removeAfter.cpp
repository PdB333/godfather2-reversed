// FUNC_NAME: Array::removeAfter
void __thiscall Array::removeAfter(int newCount)
{
    // this +0x1c: pointer to internal data structure
    int* data = *(int**)((char*)this + 0x1c);
    int count = data[0xd];                        // +0x34: current number of elements

    // Remove elements until count reaches newCount
    while (newCount < count)
    {
        // Decrement count
        data[0xd] = --count;

        // Retrieve base pointer for the element array from data[0]
        // data[0] points to a structure, whose +0x18 is a pointer to the element array
        int* elementArray = *(int**)(data[0] + 0x18);

        // Index of the element to remove is stored at data[0xae + count]
        int elemIndex = data[count + 0xae];        // +0x2b8: array of element indices

        // Write the deletion marker (data[6] = +0x18) into the element's third dword (+0x08)
        // Each element is 12 bytes, so element offset = 8 + elemIndex * 0xc
        elementArray[2 + elemIndex * 3] = data[6]; // dword index: 2 = byte 8 / 4
    }
}